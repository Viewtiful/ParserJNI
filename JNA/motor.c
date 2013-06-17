#include <jni.h>
#include <stdio.h>
#include <ktb/err.h>
#include <ktb.h>
#include <ktb/prng.h>
#include <ktb/prng_custom.h>
#include <ktb/cipher.h>
#include <ktb/keys.h>
#include <ktb/hash.h>
#include <ktb/sign.h>
#include <ktb/kdf.h>
#include <ktb/curves.h>
#include <kep/kep.h>
#include <kep/kep_sts.h>


static JNINativeMethod method_table[] = {
};

static int method_table_size = sizeof(method_table) / sizeof(method_table[0]);

jint JNI_OnLoad (JavaVM *vm, void *reserved) {
	JNIEnv *env;
	if ((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_6) != JNI_OK) {
			return JNI_ERR;
	} else {
		jclass class = (*env)->FindClass(env, "Motor");
		if (class) {
			jint ret = (*env)->RegisterNatives(env, class, method_table, method_table_size);
			(*env)->DeleteLocalRef(env, class);
			return ret == 0 ? JNI_VERSION_1_6 : JNI_ERR;
		} else {
			return JNI_ERR;
		}
	}
}

