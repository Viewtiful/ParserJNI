#!/bin/bash 

# @author Rick Ghanem
#
# Auto filter line rule : ( consider line by line )
# if @a occurs next word if contain "_" will be converted to java form
# if @ref found check if next word start with KTB_ERR and link to ktb_errno else ignore 
# if http:// transform to html <a href using link as label
# if "ktb_" detected convert function from C to JAVA .
#
# Special rules ( for lines starting with @tag ) :
# @param remove [in] | [out] | [in,out]
# @return line not modified
# @note , @warning , @attention are handled by javadoc -tag
# @retval converted to @returnvals handled by javadoc -tag 
# all lines following @retval considered return values and linked to ktb_errno
# @code line are ignored untill @endcode appears .
# @see transformed to @look to be handled by javadoc -tag
# @todo line ignored . [Warning next line considered as normal test]
# When we hit a blank line either we close paragraph or start a new one .


# To Do :
# remove constructor from javadoc
# @ref followed by unknow param ex : @ref KEP_indepth page
# Line before @code
# Kep ktpKepGetData ( false foc for return because return type changed )
# link converted C function to module (only missing parameters)


read LINE
params=($(echo $LINE | nawk -F"," '{$1=$1; print}'));
#echo "${#params[*]} parameters."
#echo ${params[*]}  >> param.log

#Control variable
blocStart=true

# create a filter function for @a
# if encounter @a check if param next 
# and convert to Java if needed
lineFilter () {
    LINE=$@
    # look if @a exist
    FOUND=`echo $LINE | grep "@a "` 
    if [ "${FOUND}" != "" ]; then
        #echo "FOUND @a ."
        PARAMS=$(echo $LINE | sed 's/@a /\n/g' | cut -d" " -f1 | awk 'FNR>1')
        #echo "PARAMS : $PARAMS ."
        for PARAM in $PARAMS; do
            #echo "For loop with $PARAM ."
            PARAMJ=`convParamToJava $PARAM`
            #echo "$PARAM --- $PARAMJ"
            PARAMJ="$PARAMJ"
            LINE=`echo $LINE | sed 's/@a '"${PARAM}"'/'"${PARAMJ}"'/g'`
        done
    fi

    # check for @ref occurence and convert following value .
    FOUND=`echo $LINE | grep "@ref "` 
    if [ "${FOUND}" != "" ]; then
        #echo "FOUND @a ."
        PARAMS=$(echo $LINE | sed 's/@ref /\n/g' | cut -d" " -f1 | awk 'FNR>1')
        for PARAM in $PARAMS; do
            FOUND=`echo $LINE | grep " KTB_ERR_"`
            if [ "${FOUND}" != "" ]; then
                LINE=`echo $LINE | sed 's/@ref//' | sed 's/'"${PARAM}"'/{@link Ktb_errno#'"${PARAM} ${PARAM}"'}/'`
            fi
        done
        if [ "`echo $LINE | grep "@ref"`" != "" ]; then 
            echo $LINE >> todo.param
        fi
    fi

    #check for http .
    #considering 1 http per line
    FOUND=`echo $LINE | grep "http://"`
    if [ "${FOUND}" != "" ]; then
        echo "[HTTP OLD] $LINE" >> todo.param
        LINE=`echo $LINE | sed 's/\//%-%/g'`
        LINK=`echo $LINE | sed 's/ /\n/g' | grep "http:" | sed 's/(//' | sed 's/).//' | sed 's/)//'`
        LINE=`echo $LINE | sed 's/'"${LINK}"'/<a href=\"'"${LINK}"'\">'"${LINK}"'<\/a>/'`
        LINE=`echo $LINE | sed 's/%-%/\//g'`
        echo "[HTTP GEN] $LINE" >> todo.param
    fi

    #check for C function name
    # look for ()
    FOUND=`echo $LINE | grep "ktb_"`
    if [ "${FOUND}" != "" ]; then
        FUNCS=$(echo $LINE | sed 's/ktb_/\nktb_/g' | cut -d" " -f1 | awk 'FNR>1')
        for FUNC in $FUNCS; do
            FUNCJ=`convParamToJava $FUNC`
            LINE=`echo $LINE | sed 's/'"${FUNC}"'/'"${FUNCJ}"'/'`
            echo "$FUNC => $FUNCJ" >> conv.func.log
        done
        
    fi
    echo $LINE
}


# UPGRADE change style to put RetVal on top .
# Format the output for @retva with JavaDoc param style .
outputRetVal ()  {
    LINE=$@
    retval=($(echo $LINE | sed 's/@retval //' | cut -d" " -f1))
    retvaldetail=$(echo $LINE | sed 's/@retval //' | sed 's/'"${retval} "'//')
    #echo "<dd><code> $retval</code> - $retvaldetail</dd>"
    echo "<code>{@linkplain Ktb_errno#$retval $retval}</code> - $retvaldetail<br />"
}

# Format the output for @param .
outputParam () {
    LINE="$@"
    # remove [in] or [out]
    echo "${LINE}" | sed 's/\[in\]//' | sed 's/\[out\]//' | sed 's/\[in,out\]//'
}

# Convert parameter FROM C to JAVA 
# exemple : public_key_size => publicKeySize
convParamToJava () {
    NAME=$1
    # Conversion is needed if a "_" exist .
    OK=$(echo $NAME | grep "_")
    if [ "${OK}" != "" ]; then
        # UPGRADE MAKE IT BETTER
        # Start conversion
        input=`echo $NAME | sed 's/_/ /g'`
        declare -a array
        array=($input)
        NAME=$(echo ${array[@]^} | sed 's/ //g')
        u=$(tr '[A-Z]' '[a-z]'<<<"${NAME:0:1}"); 
        echo $u${NAME:1}
    else
        # Return unchanged
        echo $NAME
    fi 
}

# Convert param to Java if necesseray ,check if
# param was removed and add parameters when needded
handleParam () {
    LINE=$@
    # Extract param name from "@param name description"
    PARAM=$(echo $LINE | cut -d" " -f2)
    
    # convert name to java
    PARAM=`convParamToJava $PARAM`
    
    # check if attribute in list  
    FOUND=`echo ${params[*]} | sed 's/ /\n/g' | grep ^"$PARAM"$`
    if [ "${FOUND}" != "" ]; then
        old=`echo $LINE | cut -d" " -f2`
        echo $LINE | sed 's/'"${old}"'/'"${FOUND}"'/g'
        return
    fi

    # UPGRADE keep CPARAM JAVA PARAM ...
    # if param ends with _size
    FOUND=`echo $LINE | cut -d" " -f2 | grep "_size"$`
    if [ "${FOUND}" != "" ]; then
        PREPARAM=`echo $FOUND | sed 's/_size//'`
        # test if we are wih Offset and Length
        ADD=`echo ${params[*]} | sed 's/ /\n/g' | grep "Offset"`
        if [ "${ADD}" != "" ]; then
            PREPARAM=`convParamToJava $PREPARAM`
            echo "@param ${PREPARAM}Offset the position of set in the byte array"
            echo "@param ${PREPARAM}Length byte array size"
        fi
    fi
}


# UPDATE Override read function to filter directly .

handleLine () {
    
    LINE=$@;
#    LINE="$(lineFilter $@)"

    case $LINE in
        @param*)
            LINE=$(outputParam $LINE)

            while read NEXTLINE; do
                NEXTLINE=$(lineFilter $NEXTLINE)
                NEXTLINE=$(outputParam $NEXTLINE)
                case $NEXTLINE in
                    @param* )
                        handleParam $LINE 
                        LINE=$NEXTLINE ;;
                     "")
                        handleParam $LINE  
                        handleLine $NEXTLINE 
                        break ;;
                    *) 
                        LINE="$LINE $NEXTLINE"  ;;
                esac
            done
            ;;
        @return* | @note* | @warning* | @attention* )
            echo "$LINE" # filter line
            ;;
        @retval* ) #problem if only one parameter ? or @retval is et end ?
            echo "@returnvals" #handled by javadoc parameter -tag
            # read the rest as long as there is retval keep processing
            while read NEXTLINE; do
               NEXTLINE=$(lineFilter $NEXTLINE)
                case $NEXTLINE in
                   @retval* )
                    outputRetVal $LINE 
                    LINE=$NEXTLINE ;;
                    "") outputRetVal $LINE  
                        handleLine $NEXTLINE 
                        break ;;
                    *) LINE="$LINE $NEXTLINE"  ;;
               esac
            done
            ;;
        @see*) #use custom tag
            LINE=`echo $LINE | sed 's/@see/@look/'`
            echo $LINE
            ;;
        @todo*) #ignore
            ;;
        @code) #ignore untill @endcode
            while read NEXTLINE; do
               NEXTLINE=$(lineFilter $NEXTLINE)
               case $NEXTLINE in
                   @endcode) break;;
               esac
            done
            ;;
        @*) # to do
            echo "$LINE"
            echo "$LINE" >> todo.param
            ;;
        "") # Blank line
            echo "$LINE"
            if read NEXTLINE
            then
                NEXTLINE=$(lineFilter $NEXTLINE)
                case $NEXTLINE in
                @*) handleLine $NEXTLINE ;;
                "") handleLine $NEXTLINE ;;
                *) echo "<p>"; blocStart=true; handleLine $NEXTLINE ;;
                esac
            fi
            ;;
        *)  # filter line
            echo "$LINE"
            if test $blocStart == true && read NEXTLINE
            then
                NEXTLINE=$(lineFilter $NEXTLINE)  
                case $NEXTLINE in
                    # We never Know
                    @*) echo "</p>"; blocStart=false; handleLine $NEXTLINE ;;
                    "") echo "</p>"; blocStart=false; handleLine $NEXTLINE ;;
                    *) handleLine $NEXTLINE ;;
                esac
            fi
            ;;
    esac

}



echo "<p>" # to review !
while read LINE; do
#    echo "treating next"
#read LINE
#LINE=`echo $LINE | sed 's/\*//g'`
LINE=$(lineFilter $LINE)
handleLine $LINE
done

