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
#include <kep/kep_dh.h>
#include <kep/kep_dhpass.h>
#include <kep/kep_sts.h>


	typedef struct
	{
		void *ctxRef;
		JNIEnv *env;
	} contextWrapper;

	JNIEXPORT jlong JNICALL JNI_gen_jni_ktb_kep_dh_t_create(JNIEnv *env, jclass cls) {

		contextWrapper *ctxWrp = (contextWrapper *)malloc(sizeof(contextWrapper));
		ktb_kep_dh_t *C_ctx = (ktb_kep_dh_t *)malloc(sizeof(ktb_kep_dh_t));
		ctxWrp->ctxRef = C_ctx;
		return ctxWrp;
	}

	JNIEXPORT void JNICALL JNI_gen_jni_ktb_kep_dh_t_free(JNIEnv *env, jclass cls, jlong mInternal) {

		ktb_kep_dh_t *C_ctx = (ktb_kep_dh_t *)mInternal;
		free(C_ctx);
	}

	JNIEXPORT jlong JNICALL JNI_gen_jni_ktb_kep_dh_t_get_struct_size(JNIEnv *env, jclass cls) {

		return sizeof(ktb_kep_dh_t);
	}

	JNIEXPORT jint JNICALL JNI_gen_jni_ktb_kep_dh_t_get_dummy(JNIEnv *env, jclass cls, jlong mInternal) {

		ktb_kep_dh_t *C_ctx;
		if(mInternal != 0)
			C_ctx = (ktb_kep_dh_t *)((contextWrapper *)mInternal)->ctxRef;
		else
			C_ctx = NULL;

		return C_ctx->dummy;
	}

	JNIEXPORT void JNICALL JNI_gen_jni_ktb_kep_dh_t_set_dummy(JNIEnv *env, jclass cls, jlong mInternal,jint dummy) {

		ktb_kep_dh_t *C_ctx;
		if(mInternal != 0)
			C_ctx = (ktb_kep_dh_t *)((contextWrapper *)mInternal)->ctxRef;
		else
			C_ctx = NULL;
		C_ctx->dummy = dummy;
	}

	JNIEXPORT jlong JNICALL JNI_gen_jni_ktb_kep_dh_pass_t_create(JNIEnv *env, jclass cls) {

		contextWrapper *ctxWrp = (contextWrapper *)malloc(sizeof(contextWrapper));
		ktb_kep_dh_pass_t *C_ctx = (ktb_kep_dh_pass_t *)malloc(sizeof(ktb_kep_dh_pass_t));
		ctxWrp->ctxRef = C_ctx;
		return ctxWrp;
	}

	JNIEXPORT void JNICALL JNI_gen_jni_ktb_kep_dh_pass_t_free(JNIEnv *env, jclass cls, jlong mInternal) {

		ktb_kep_dh_pass_t *C_ctx = (ktb_kep_dh_pass_t *)mInternal;
		free(C_ctx);
	}

	JNIEXPORT jlong JNICALL JNI_gen_jni_ktb_kep_dh_pass_t_get_struct_size(JNIEnv *env, jclass cls) {

		return sizeof(ktb_kep_dh_pass_t);
	}

	JNIEXPORT jobject JNICALL JNI_gen_jni_ktb_kep_dh_pass_t_get_cipher_algo(JNIEnv *env, jclass cls, jlong mInternal) {

		ktb_kep_dh_pass_t *C_ctx;
		if(mInternal != 0)
			C_ctx = (ktb_kep_dh_pass_t *)((contextWrapper *)mInternal)->ctxRef;
		else
			C_ctx = NULL;

		jobject JNI_result;
		jclass retObjCls;
		retObjCls = (*env)->FindClass(env, "ArcanaJNI$ktb_cipher_algo_t");
		jmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, "values", "()[LArcanaJNI$ktb_cipher_algo_t;");
		jobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);

		int arrayLength = (*env)->GetArrayLength(env, valuesArray);

		int i, val;
		jmethodID getVal;
		getVal = (*env)->GetMethodID(env, retObjCls, "getValue", "()I");

		for(i = 0; i < arrayLength; ++i) {
			JNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);
			val = (*env)->CallIntMethod(env, JNI_result, getVal);
			if(val == C_ctx->cipher_algo) {
				break;
			}
		}

		return JNI_result;
	}

	JNIEXPORT jbyteArray JNICALL JNI_gen_jni_ktb_kep_dh_pass_t_get_discuss_key(JNIEnv *env, jclass cls, jlong mInternal) {

		ktb_kep_dh_pass_t *C_ctx;
		if(mInternal != 0)
			C_ctx = (ktb_kep_dh_pass_t *)((contextWrapper *)mInternal)->ctxRef;
		else
			C_ctx = NULL;

		jbyteArray result = (*env)->NewByteArray(env, C_ctx->discuss_key_size);
		(*env)->SetByteArrayRegion(env, result, 0, C_ctx->discuss_key_size, C_ctx->discuss_key);
		return result;
	}

	JNIEXPORT jlong JNICALL JNI_gen_jni_ktb_kep_dh_pass_t_get_discuss_key_size(JNIEnv *env, jclass cls, jlong mInternal) {

		ktb_kep_dh_pass_t *C_ctx;
		if(mInternal != 0)
			C_ctx = (ktb_kep_dh_pass_t *)((contextWrapper *)mInternal)->ctxRef;
		else
			C_ctx = NULL;

		return C_ctx->discuss_key_size;
	}

	JNIEXPORT void JNICALL JNI_gen_jni_ktb_kep_dh_pass_t_set_cipher_algo(JNIEnv *env, jclass cls, jlong mInternal,jobject cipher_algo) {

		ktb_kep_dh_pass_t *C_ctx;
		if(mInternal != 0)
			C_ctx = (ktb_kep_dh_pass_t *)((contextWrapper *)mInternal)->ctxRef;
		else
			C_ctx = NULL;
		jclass enm_cipher_algo;
		enm_cipher_algo = (*env)->GetObjectClass(env, cipher_algo);
		jmethodID get_cipher_algo = (*env)->GetMethodID(env, enm_cipher_algo, "getValue", "()I");
		jint cipher_algo_value = (*env)->CallIntMethod(env, cipher_algo, get_cipher_algo);
		ktb_cipher_algo_t C_cipher_algo = (ktb_cipher_algo_t)cipher_algo_value;
		C_ctx->cipher_algo = C_cipher_algo;
	}

	JNIEXPORT void JNICALL JNI_gen_jni_ktb_kep_dh_pass_t_set_discuss_key(JNIEnv *env, jclass cls, jlong mInternal,jbyteArray discuss_key) {

		ktb_kep_dh_pass_t *C_ctx;
		if(mInternal != 0)
			C_ctx = (ktb_kep_dh_pass_t *)((contextWrapper *)mInternal)->ctxRef;
		else
			C_ctx = NULL;
		jbyte * C_discuss_key;
		size_t C_discuss_key_length = (*env)->GetArrayLength(env, discuss_key);
		C_discuss_key = (jbyte *)malloc(C_discuss_key_length);
		C_discuss_key = (*env)->GetByteArrayElements(env, discuss_key, NULL);
		C_ctx->discuss_key = C_discuss_key;
	}

	JNIEXPORT void JNICALL JNI_gen_jni_ktb_kep_dh_pass_t_set_discuss_key_size(JNIEnv *env, jclass cls, jlong mInternal,jlong discuss_key_size) {

		ktb_kep_dh_pass_t *C_ctx;
		if(mInternal != 0)
			C_ctx = (ktb_kep_dh_pass_t *)((contextWrapper *)mInternal)->ctxRef;
		else
			C_ctx = NULL;
		C_ctx->discuss_key_size = discuss_key_size;
	}

	JNIEXPORT jlong JNICALL JNI_gen_jni_ktb_kep_sts_t_create(JNIEnv *env, jclass cls) {

		contextWrapper *ctxWrp = (contextWrapper *)malloc(sizeof(contextWrapper));
		ktb_kep_sts_t *C_ctx = (ktb_kep_sts_t *)malloc(sizeof(ktb_kep_sts_t));
		ctxWrp->ctxRef = C_ctx;
		return ctxWrp;
	}

	JNIEXPORT void JNICALL JNI_gen_jni_ktb_kep_sts_t_free(JNIEnv *env, jclass cls, jlong mInternal) {

		ktb_kep_sts_t *C_ctx = (ktb_kep_sts_t *)mInternal;
		free(C_ctx);
	}

	JNIEXPORT jlong JNICALL JNI_gen_jni_ktb_kep_sts_t_get_struct_size(JNIEnv *env, jclass cls) {

		return sizeof(ktb_kep_sts_t);
	}

	JNIEXPORT jobject JNICALL JNI_gen_jni_ktb_kep_sts_t_get_cipher_algo(JNIEnv *env, jclass cls, jlong mInternal) {

		ktb_kep_sts_t *C_ctx;
		if(mInternal != 0)
			C_ctx = (ktb_kep_sts_t *)((contextWrapper *)mInternal)->ctxRef;
		else
			C_ctx = NULL;

		jobject JNI_result;
		jclass retObjCls;
		retObjCls = (*env)->FindClass(env, "ArcanaJNI$ktb_cipher_algo_t");
		jmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, "values", "()[LArcanaJNI$ktb_cipher_algo_t;");
		jobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);

		int arrayLength = (*env)->GetArrayLength(env, valuesArray);

		int i, val;
		jmethodID getVal;
		getVal = (*env)->GetMethodID(env, retObjCls, "getValue", "()I");

		for(i = 0; i < arrayLength; ++i) {
			JNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);
			val = (*env)->CallIntMethod(env, JNI_result, getVal);
			if(val == C_ctx->cipher_algo) {
				break;
			}
		}

		return JNI_result;
	}

	JNIEXPORT jlong JNICALL JNI_gen_jni_ktb_kep_sts_t_get_peer_public_key(JNIEnv *env, jclass cls, jlong mInternal) {

		ktb_kep_sts_t *C_ctx;
		if(mInternal != 0)
			C_ctx = (ktb_kep_sts_t *)((contextWrapper *)mInternal)->ctxRef;
		else
			C_ctx = NULL;

		return C_ctx->peer_public_key;
	}

	JNIEXPORT jlong JNICALL JNI_gen_jni_ktb_kep_sts_t_get_self_private_key(JNIEnv *env, jclass cls, jlong mInternal) {

		ktb_kep_sts_t *C_ctx;
		if(mInternal != 0)
			C_ctx = (ktb_kep_sts_t *)((contextWrapper *)mInternal)->ctxRef;
		else
			C_ctx = NULL;

		return C_ctx->self_private_key;
	}

	JNIEXPORT void JNICALL JNI_gen_jni_ktb_kep_sts_t_set_cipher_algo(JNIEnv *env, jclass cls, jlong mInternal,jobject cipher_algo) {

		ktb_kep_sts_t *C_ctx;
		if(mInternal != 0)
			C_ctx = (ktb_kep_sts_t *)((contextWrapper *)mInternal)->ctxRef;
		else
			C_ctx = NULL;
		jclass enm_cipher_algo;
		enm_cipher_algo = (*env)->GetObjectClass(env, cipher_algo);
		jmethodID get_cipher_algo = (*env)->GetMethodID(env, enm_cipher_algo, "getValue", "()I");
		jint cipher_algo_value = (*env)->CallIntMethod(env, cipher_algo, get_cipher_algo);
		ktb_cipher_algo_t C_cipher_algo = (ktb_cipher_algo_t)cipher_algo_value;
		C_ctx->cipher_algo = C_cipher_algo;
	}

	JNIEXPORT void JNICALL JNI_gen_jni_ktb_kep_sts_t_set_peer_public_key(JNIEnv *env, jclass cls, jlong mInternal,jlong peer_public_key) {

		ktb_kep_sts_t *C_ctx;
		if(mInternal != 0)
			C_ctx = (ktb_kep_sts_t *)((contextWrapper *)mInternal)->ctxRef;
		else
			C_ctx = NULL;
		C_ctx->peer_public_key = (const_ktb_public_key_t)((contextWrapper *)peer_public_key)->ctxRef;
		((contextWrapper *)peer_public_key)->env = env;
	}

	JNIEXPORT void JNICALL JNI_gen_jni_ktb_kep_sts_t_set_self_private_key(JNIEnv *env, jclass cls, jlong mInternal,jlong self_private_key) {

		ktb_kep_sts_t *C_ctx;
		if(mInternal != 0)
			C_ctx = (ktb_kep_sts_t *)((contextWrapper *)mInternal)->ctxRef;
		else
			C_ctx = NULL;
		C_ctx->self_private_key = (const_ktb_private_key_t)((contextWrapper *)self_private_key)->ctxRef;
		((contextWrapper *)self_private_key)->env = env;
	}

	JNIEXPORT jobject JNICALL JNI_ktb_kep_init(JNIEnv *env, jclass cls, jobject ctx,jlong prng,jobject algo,jlong algo_data,jlong algo_data_size,jstring curve_id,jobject hash_algo,jlong secret_key_size,jint peer_count) {

		jobject JNI_result;

		ktb_kep_ctx_t C_ctx;
		contextWrapper *ctxWrp1 = (contextWrapper *)malloc(sizeof(contextWrapper));
		ctxWrp1->env = env;

		ktb_prng_t C_prng;
		if(prng != 0) {
			C_prng = (ktb_prng_t)((contextWrapper *)prng)->ctxRef;
			((contextWrapper *)prng)->env = env;
		}
		else
			C_prng = NULL;

		jclass enm_algo;
		enm_algo = (*env)->GetObjectClass(env, algo);
		jmethodID get_algo = (*env)->GetMethodID(env, enm_algo, "getValue", "()I");
		jint algo_value = (*env)->CallIntMethod(env, algo, get_algo);
		ktb_kep_algo_t C_algo = (ktb_kep_algo_t)algo_value;

		ktb_kep_algo_data_t C_algo_data;
		if(algo_data != 0) {
			C_algo_data = (ktb_kep_algo_data_t)((contextWrapper *)algo_data)->ctxRef;
			((contextWrapper *)algo_data)->env = env;
		}
		else
			C_algo_data = NULL;

		size_t C_algo_data_size = (size_t) algo_data_size;

		char * C_curve_id;
		C_curve_id = (char *)(*env)->GetStringUTFChars(env, curve_id, NULL);
		if(C_curve_id == NULL) {
			 fprintf(stderr, " Out of memory");
			 exit(1);
		}

		jclass enm_hash_algo;
		enm_hash_algo = (*env)->GetObjectClass(env, hash_algo);
		jmethodID get_hash_algo = (*env)->GetMethodID(env, enm_hash_algo, "getValue", "()I");
		jint hash_algo_value = (*env)->CallIntMethod(env, hash_algo, get_hash_algo);
		ktb_hash_algo_t C_hash_algo = (ktb_hash_algo_t)hash_algo_value;

		size_t C_secret_key_size = (size_t) secret_key_size;

		int C_peer_count = (int) peer_count;

		ktb_errno tempJNI_result = ktb_kep_init (&C_ctx, C_prng, C_algo, C_algo_data, C_algo_data_size, C_curve_id, C_hash_algo, C_secret_key_size, C_peer_count);

		ctxWrp1->ctxRef = C_ctx;
		jclass adrWrp_ctx;
		jmethodID setAddr_ctx;
		jlong arg_ctx;

		adrWrp_ctx = (*env)->GetObjectClass(env, ctx);
		setAddr_ctx = (*env)->GetMethodID(env, adrWrp_ctx, "setAddress", "(J)V");
		arg_ctx = (jlong) ctxWrp1;
		(*env)->CallVoidMethod(env, ctx, setAddr_ctx, arg_ctx);

		jclass retObjCls = (*env)->FindClass(env, "ArcanaJNI$ktb_errno");
		jmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, "values", "()[LArcanaJNI$ktb_errno;");
		jobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);

		int arrayLength = (*env)->GetArrayLength(env, valuesArray);

		int i, val;
		jmethodID getVal;
		getVal = (*env)->GetMethodID(env, retObjCls, "getValue", "()I");

		for(i = 0; i < arrayLength; ++i)
		{
			JNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);
			val = (*env)->CallIntMethod(env, JNI_result, getVal);
			if(val == tempJNI_result) {
				break;
			}
		}
		return JNI_result;

	}

	JNIEXPORT void JNICALL JNI_ktb_kep_clear(JNIEnv *env, jclass cls, jlong ctx) {

		ktb_kep_ctx_t C_ctx;
		if(ctx != 0) {
			C_ctx = (ktb_kep_ctx_t)((contextWrapper *)ctx)->ctxRef;
			((contextWrapper *)ctx)->env = env;
		}
		else
			C_ctx = NULL;

		  ktb_kep_clear (C_ctx);

	}

	JNIEXPORT jbyteArray JNICALL JNI_ktb_kep_get_data(JNIEnv *env, jclass cls, jlong ctx) {

		jbyteArray JNI_result;

		ktb_kep_ctx_t C_ctx;
		if(ctx != 0) {
			C_ctx = (ktb_kep_ctx_t)((contextWrapper *)ctx)->ctxRef;
			((contextWrapper *)ctx)->env = env;
		}
		else
			C_ctx = NULL;

		size_t C_size;

		void* tempJNI_result = (void*)ktb_kep_get_data (C_ctx, &C_size);

		JNI_result = (*env)->NewByteArray(env, C_size);
		(*env)->SetByteArrayRegion(env, JNI_result, 0, C_size, (jbyte *)tempJNI_result);
		return JNI_result;
	}

	JNIEXPORT jobject JNICALL JNI_ktb_kep_put_data(JNIEnv *env, jclass cls, jlong ctx,jbyteArray peer_data,jobject continue_exchange) {

		jobject JNI_result;

		ktb_kep_ctx_t C_ctx;
		if(ctx != 0) {
			C_ctx = (ktb_kep_ctx_t)((contextWrapper *)ctx)->ctxRef;
			((contextWrapper *)ctx)->env = env;
		}
		else
			C_ctx = NULL;

		jbyte * C_peer_data;
		int C_peer_data_size = (*env)->GetArrayLength(env, peer_data);
		C_peer_data = (jbyte *)malloc(C_peer_data_size);
		C_peer_data = (*env)->GetByteArrayElements(env, peer_data, NULL);

		bool C_continue_exchange;

		ktb_errno tempJNI_result = ktb_kep_put_data (C_ctx, C_peer_data, C_peer_data_size, &C_continue_exchange);

		(*env)->SetByteArrayRegion(env, peer_data, 0, C_peer_data_size, C_peer_data);
		int i_C_peer_data;
		for(i_C_peer_data = 0; i_C_peer_data < C_peer_data_size; ++i_C_peer_data)
			C_peer_data[i_C_peer_data] = 0;
		free(C_peer_data);

		jclass boolWrp;
		jmethodID setVal;
		jboolean arg;
		boolWrp = (*env)->GetObjectClass(env, continue_exchange);
		setVal = (*env)->GetMethodID(env, boolWrp, "setValue", "(Z)V");
		arg = (jboolean) C_continue_exchange;
		(*env)->CallVoidMethod(env, continue_exchange, setVal, arg);

		jclass retObjCls = (*env)->FindClass(env, "ArcanaJNI$ktb_errno");
		jmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, "values", "()[LArcanaJNI$ktb_errno;");
		jobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);

		int arrayLength = (*env)->GetArrayLength(env, valuesArray);

		int i, val;
		jmethodID getVal;
		getVal = (*env)->GetMethodID(env, retObjCls, "getValue", "()I");

		for(i = 0; i < arrayLength; ++i)
		{
			JNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);
			val = (*env)->CallIntMethod(env, JNI_result, getVal);
			if(val == tempJNI_result) {
				break;
			}
		}
		return JNI_result;

	}

	JNIEXPORT jobject JNICALL JNI_ktb_kep_finalise(JNIEnv *env, jclass cls, jlong ctx,jbyteArray secret_key) {

		jobject JNI_result;

		ktb_kep_ctx_t C_ctx;
		if(ctx != 0) {
			C_ctx = (ktb_kep_ctx_t)((contextWrapper *)ctx)->ctxRef;
			((contextWrapper *)ctx)->env = env;
		}
		else
			C_ctx = NULL;

		jbyte * C_secret_key;
		int C_secret_key_size = (*env)->GetArrayLength(env, secret_key);
		C_secret_key = (jbyte *)malloc(C_secret_key_size);
		C_secret_key = (*env)->GetByteArrayElements(env, secret_key, NULL);

		ktb_errno tempJNI_result = ktb_kep_finalise (C_ctx, C_secret_key, C_secret_key_size);

		(*env)->SetByteArrayRegion(env, secret_key, 0, C_secret_key_size, C_secret_key);
		int i_C_secret_key;
		for(i_C_secret_key = 0; i_C_secret_key < C_secret_key_size; ++i_C_secret_key)
			C_secret_key[i_C_secret_key] = 0;
		free(C_secret_key);

		jclass retObjCls = (*env)->FindClass(env, "ArcanaJNI$ktb_errno");
		jmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, "values", "()[LArcanaJNI$ktb_errno;");
		jobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);

		int arrayLength = (*env)->GetArrayLength(env, valuesArray);

		int i, val;
		jmethodID getVal;
		getVal = (*env)->GetMethodID(env, retObjCls, "getValue", "()I");

		for(i = 0; i < arrayLength; ++i)
		{
			JNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);
			val = (*env)->CallIntMethod(env, JNI_result, getVal);
			if(val == tempJNI_result) {
				break;
			}
		}
		return JNI_result;

	}

	JNIEXPORT jstring JNICALL JNI_ktb_kep_get_algo_name(JNIEnv *env, jclass cls, jobject algo) {

		jstring JNI_result;

		jclass enm_algo;
		enm_algo = (*env)->GetObjectClass(env, algo);
		jmethodID get_algo = (*env)->GetMethodID(env, enm_algo, "getValue", "()I");
		jint algo_value = (*env)->CallIntMethod(env, algo, get_algo);
		ktb_kep_algo_t C_algo = (ktb_kep_algo_t)algo_value;

		char * tempJNI_result = (char *)ktb_kep_get_algo_name (C_algo);

		JNI_result = (*env)->NewStringUTF(env, tempJNI_result);
		 return JNI_result;
	}

	JNIEXPORT jobject JNICALL JNI_ktb_init(JNIEnv *env, jclass cls) {

		jobject JNI_result;

		ktb_errno tempJNI_result = ktb_init ();

		jclass retObjCls = (*env)->FindClass(env, "ArcanaJNI$ktb_errno");
		jmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, "values", "()[LArcanaJNI$ktb_errno;");
		jobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);

		int arrayLength = (*env)->GetArrayLength(env, valuesArray);

		int i, val;
		jmethodID getVal;
		getVal = (*env)->GetMethodID(env, retObjCls, "getValue", "()I");

		for(i = 0; i < arrayLength; ++i)
		{
			JNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);
			val = (*env)->CallIntMethod(env, JNI_result, getVal);
			if(val == tempJNI_result) {
				break;
			}
		}
		return JNI_result;

	}

	JNIEXPORT void JNICALL JNI_ktb_clear(JNIEnv *env, jclass cls) {

		  ktb_clear ();

	}

	JNIEXPORT jobject JNICALL JNI_ktb_sign_init(JNIEnv *env, jclass cls, jobject ctx,jobject algo) {

		jobject JNI_result;

		ktb_sign_ctx_t C_ctx;
		contextWrapper *ctxWrp1 = (contextWrapper *)malloc(sizeof(contextWrapper));
		ctxWrp1->env = env;

		jclass enm_algo;
		enm_algo = (*env)->GetObjectClass(env, algo);
		jmethodID get_algo = (*env)->GetMethodID(env, enm_algo, "getValue", "()I");
		jint algo_value = (*env)->CallIntMethod(env, algo, get_algo);
		ktb_hash_algo_t C_algo = (ktb_hash_algo_t)algo_value;

		ktb_errno tempJNI_result = ktb_sign_init (&C_ctx, C_algo);

		ctxWrp1->ctxRef = C_ctx;
		jclass adrWrp_ctx;
		jmethodID setAddr_ctx;
		jlong arg_ctx;

		adrWrp_ctx = (*env)->GetObjectClass(env, ctx);
		setAddr_ctx = (*env)->GetMethodID(env, adrWrp_ctx, "setAddress", "(J)V");
		arg_ctx = (jlong) ctxWrp1;
		(*env)->CallVoidMethod(env, ctx, setAddr_ctx, arg_ctx);

		jclass retObjCls = (*env)->FindClass(env, "ArcanaJNI$ktb_errno");
		jmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, "values", "()[LArcanaJNI$ktb_errno;");
		jobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);

		int arrayLength = (*env)->GetArrayLength(env, valuesArray);

		int i, val;
		jmethodID getVal;
		getVal = (*env)->GetMethodID(env, retObjCls, "getValue", "()I");

		for(i = 0; i < arrayLength; ++i)
		{
			JNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);
			val = (*env)->CallIntMethod(env, JNI_result, getVal);
			if(val == tempJNI_result) {
				break;
			}
		}
		return JNI_result;

	}

	JNIEXPORT void JNICALL JNI_ktb_sign_clear(JNIEnv *env, jclass cls, jlong ctx) {

		ktb_sign_ctx_t C_ctx;
		if(ctx != 0) {
			C_ctx = (ktb_sign_ctx_t)((contextWrapper *)ctx)->ctxRef;
			((contextWrapper *)ctx)->env = env;
		}
		else
			C_ctx = NULL;

		  ktb_sign_clear (C_ctx);

	}

	JNIEXPORT jobject JNICALL JNI_ktb_sign_reset(JNIEnv *env, jclass cls, jlong ctx) {

		jobject JNI_result;

		ktb_sign_ctx_t C_ctx;
		if(ctx != 0) {
			C_ctx = (ktb_sign_ctx_t)((contextWrapper *)ctx)->ctxRef;
			((contextWrapper *)ctx)->env = env;
		}
		else
			C_ctx = NULL;

		ktb_errno tempJNI_result = ktb_sign_reset (C_ctx);

		jclass retObjCls = (*env)->FindClass(env, "ArcanaJNI$ktb_errno");
		jmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, "values", "()[LArcanaJNI$ktb_errno;");
		jobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);

		int arrayLength = (*env)->GetArrayLength(env, valuesArray);

		int i, val;
		jmethodID getVal;
		getVal = (*env)->GetMethodID(env, retObjCls, "getValue", "()I");

		for(i = 0; i < arrayLength; ++i)
		{
			JNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);
			val = (*env)->CallIntMethod(env, JNI_result, getVal);
			if(val == tempJNI_result) {
				break;
			}
		}
		return JNI_result;

	}

	JNIEXPORT jobject JNICALL JNI_ktb_sign_process(JNIEnv *env, jclass cls, jlong ctx,jbyteArray data) {

		jobject JNI_result;

		ktb_sign_ctx_t C_ctx;
		if(ctx != 0) {
			C_ctx = (ktb_sign_ctx_t)((contextWrapper *)ctx)->ctxRef;
			((contextWrapper *)ctx)->env = env;
		}
		else
			C_ctx = NULL;

		jbyte * C_data;
		int C_data_size = (*env)->GetArrayLength(env, data);
		C_data = (jbyte *)malloc(C_data_size);
		C_data = (*env)->GetByteArrayElements(env, data, NULL);

		ktb_errno tempJNI_result = ktb_sign_process (C_ctx, C_data, C_data_size);

		(*env)->SetByteArrayRegion(env, data, 0, C_data_size, C_data);
		int i_C_data;
		for(i_C_data = 0; i_C_data < C_data_size; ++i_C_data)
			C_data[i_C_data] = 0;
		free(C_data);

		jclass retObjCls = (*env)->FindClass(env, "ArcanaJNI$ktb_errno");
		jmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, "values", "()[LArcanaJNI$ktb_errno;");
		jobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);

		int arrayLength = (*env)->GetArrayLength(env, valuesArray);

		int i, val;
		jmethodID getVal;
		getVal = (*env)->GetMethodID(env, retObjCls, "getValue", "()I");

		for(i = 0; i < arrayLength; ++i)
		{
			JNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);
			val = (*env)->CallIntMethod(env, JNI_result, getVal);
			if(val == tempJNI_result) {
				break;
			}
		}
		return JNI_result;

	}

	JNIEXPORT jobject JNICALL JNI_ktb_sign_finalise(JNIEnv *env, jclass cls, jlong ctx) {

		jobject JNI_result;

		ktb_sign_ctx_t C_ctx;
		if(ctx != 0) {
			C_ctx = (ktb_sign_ctx_t)((contextWrapper *)ctx)->ctxRef;
			((contextWrapper *)ctx)->env = env;
		}
		else
			C_ctx = NULL;

		ktb_errno tempJNI_result = ktb_sign_finalise (C_ctx);

		jclass retObjCls = (*env)->FindClass(env, "ArcanaJNI$ktb_errno");
		jmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, "values", "()[LArcanaJNI$ktb_errno;");
		jobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);

		int arrayLength = (*env)->GetArrayLength(env, valuesArray);

		int i, val;
		jmethodID getVal;
		getVal = (*env)->GetMethodID(env, retObjCls, "getValue", "()I");

		for(i = 0; i < arrayLength; ++i)
		{
			JNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);
			val = (*env)->CallIntMethod(env, JNI_result, getVal);
			if(val == tempJNI_result) {
				break;
			}
		}
		return JNI_result;

	}

	JNIEXPORT jobject JNICALL JNI_ktb_sign_set_public_key(JNIEnv *env, jclass cls, jlong ctx,jlong public_key) {

		jobject JNI_result;

		ktb_sign_ctx_t C_ctx;
		if(ctx != 0) {
			C_ctx = (ktb_sign_ctx_t)((contextWrapper *)ctx)->ctxRef;
			((contextWrapper *)ctx)->env = env;
		}
		else
			C_ctx = NULL;

		const_ktb_public_key_t C_public_key;
		if(public_key != 0) {
			C_public_key = (const_ktb_public_key_t)((contextWrapper *)public_key)->ctxRef;
			((contextWrapper *)public_key)->env = env;
		}
		else
			C_public_key = NULL;

		ktb_errno tempJNI_result = ktb_sign_set_public_key (C_ctx, C_public_key);

		jclass retObjCls = (*env)->FindClass(env, "ArcanaJNI$ktb_errno");
		jmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, "values", "()[LArcanaJNI$ktb_errno;");
		jobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);

		int arrayLength = (*env)->GetArrayLength(env, valuesArray);

		int i, val;
		jmethodID getVal;
		getVal = (*env)->GetMethodID(env, retObjCls, "getValue", "()I");

		for(i = 0; i < arrayLength; ++i)
		{
			JNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);
			val = (*env)->CallIntMethod(env, JNI_result, getVal);
			if(val == tempJNI_result) {
				break;
			}
		}
		return JNI_result;

	}

	JNIEXPORT jobject JNICALL JNI_ktb_sign_verify(JNIEnv *env, jclass cls, jlong ctx,jbyteArray signature,jobject is_valid) {

		jobject JNI_result;

		ktb_sign_ctx_t C_ctx;
		if(ctx != 0) {
			C_ctx = (ktb_sign_ctx_t)((contextWrapper *)ctx)->ctxRef;
			((contextWrapper *)ctx)->env = env;
		}
		else
			C_ctx = NULL;

		jbyte * C_signature;
		int C_signature_size = (*env)->GetArrayLength(env, signature);
		C_signature = (jbyte *)malloc(C_signature_size);
		C_signature = (*env)->GetByteArrayElements(env, signature, NULL);

		bool C_is_valid;

		ktb_errno tempJNI_result = ktb_sign_verify (C_ctx, C_signature, C_signature_size, &C_is_valid);

		(*env)->SetByteArrayRegion(env, signature, 0, C_signature_size, C_signature);
		int i_C_signature;
		for(i_C_signature = 0; i_C_signature < C_signature_size; ++i_C_signature)
			C_signature[i_C_signature] = 0;
		free(C_signature);

		jclass boolWrp;
		jmethodID setVal;
		jboolean arg;
		boolWrp = (*env)->GetObjectClass(env, is_valid);
		setVal = (*env)->GetMethodID(env, boolWrp, "setValue", "(Z)V");
		arg = (jboolean) C_is_valid;
		(*env)->CallVoidMethod(env, is_valid, setVal, arg);

		jclass retObjCls = (*env)->FindClass(env, "ArcanaJNI$ktb_errno");
		jmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, "values", "()[LArcanaJNI$ktb_errno;");
		jobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);

		int arrayLength = (*env)->GetArrayLength(env, valuesArray);

		int i, val;
		jmethodID getVal;
		getVal = (*env)->GetMethodID(env, retObjCls, "getValue", "()I");

		for(i = 0; i < arrayLength; ++i)
		{
			JNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);
			val = (*env)->CallIntMethod(env, JNI_result, getVal);
			if(val == tempJNI_result) {
				break;
			}
		}
		return JNI_result;

	}

	JNIEXPORT jobject JNICALL JNI_ktb_sign_verify_block(JNIEnv *env, jclass cls, jobject algo,jlong public_key,jbyteArray data,jbyteArray signature,jobject is_valid) {

		jobject JNI_result;

		jclass enm_algo;
		enm_algo = (*env)->GetObjectClass(env, algo);
		jmethodID get_algo = (*env)->GetMethodID(env, enm_algo, "getValue", "()I");
		jint algo_value = (*env)->CallIntMethod(env, algo, get_algo);
		ktb_hash_algo_t C_algo = (ktb_hash_algo_t)algo_value;

		const_ktb_public_key_t C_public_key;
		if(public_key != 0) {
			C_public_key = (const_ktb_public_key_t)((contextWrapper *)public_key)->ctxRef;
			((contextWrapper *)public_key)->env = env;
		}
		else
			C_public_key = NULL;

		jbyte * C_data;
		int C_data_size = (*env)->GetArrayLength(env, data);
		C_data = (jbyte *)malloc(C_data_size);
		C_data = (*env)->GetByteArrayElements(env, data, NULL);

		jbyte * C_signature;
		int C_signature_size = (*env)->GetArrayLength(env, signature);
		C_signature = (jbyte *)malloc(C_signature_size);
		C_signature = (*env)->GetByteArrayElements(env, signature, NULL);

		bool C_is_valid;

		ktb_errno tempJNI_result = ktb_sign_verify_block (C_algo, C_public_key, C_data, C_data_size, C_signature, C_signature_size, &C_is_valid);

		(*env)->SetByteArrayRegion(env, data, 0, C_data_size, C_data);
		int i_C_data;
		for(i_C_data = 0; i_C_data < C_data_size; ++i_C_data)
			C_data[i_C_data] = 0;
		free(C_data);

		(*env)->SetByteArrayRegion(env, signature, 0, C_signature_size, C_signature);
		int i_C_signature;
		for(i_C_signature = 0; i_C_signature < C_signature_size; ++i_C_signature)
			C_signature[i_C_signature] = 0;
		free(C_signature);

		jclass boolWrp;
		jmethodID setVal;
		jboolean arg;
		boolWrp = (*env)->GetObjectClass(env, is_valid);
		setVal = (*env)->GetMethodID(env, boolWrp, "setValue", "(Z)V");
		arg = (jboolean) C_is_valid;
		(*env)->CallVoidMethod(env, is_valid, setVal, arg);

		jclass retObjCls = (*env)->FindClass(env, "ArcanaJNI$ktb_errno");
		jmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, "values", "()[LArcanaJNI$ktb_errno;");
		jobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);

		int arrayLength = (*env)->GetArrayLength(env, valuesArray);

		int i, val;
		jmethodID getVal;
		getVal = (*env)->GetMethodID(env, retObjCls, "getValue", "()I");

		for(i = 0; i < arrayLength; ++i)
		{
			JNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);
			val = (*env)->CallIntMethod(env, JNI_result, getVal);
			if(val == tempJNI_result) {
				break;
			}
		}
		return JNI_result;

	}

	JNIEXPORT jobject JNICALL JNI_ktb_sign_set_private_key(JNIEnv *env, jclass cls, jlong ctx,jlong private_key,jlong prng) {

		jobject JNI_result;

		ktb_sign_ctx_t C_ctx;
		if(ctx != 0) {
			C_ctx = (ktb_sign_ctx_t)((contextWrapper *)ctx)->ctxRef;
			((contextWrapper *)ctx)->env = env;
		}
		else
			C_ctx = NULL;

		const_ktb_private_key_t C_private_key;
		if(private_key != 0) {
			C_private_key = (const_ktb_private_key_t)((contextWrapper *)private_key)->ctxRef;
			((contextWrapper *)private_key)->env = env;
		}
		else
			C_private_key = NULL;

		ktb_prng_t C_prng;
		if(prng != 0) {
			C_prng = (ktb_prng_t)((contextWrapper *)prng)->ctxRef;
			((contextWrapper *)prng)->env = env;
		}
		else
			C_prng = NULL;

		ktb_errno tempJNI_result = ktb_sign_set_private_key (C_ctx, C_private_key, C_prng);

		jclass retObjCls = (*env)->FindClass(env, "ArcanaJNI$ktb_errno");
		jmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, "values", "()[LArcanaJNI$ktb_errno;");
		jobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);

		int arrayLength = (*env)->GetArrayLength(env, valuesArray);

		int i, val;
		jmethodID getVal;
		getVal = (*env)->GetMethodID(env, retObjCls, "getValue", "()I");

		for(i = 0; i < arrayLength; ++i)
		{
			JNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);
			val = (*env)->CallIntMethod(env, JNI_result, getVal);
			if(val == tempJNI_result) {
				break;
			}
		}
		return JNI_result;

	}

	JNIEXPORT jlong JNICALL JNI_ktb_sign_get_sign_size(JNIEnv *env, jclass cls, jlong ctx) {

		jlong JNI_result;

		ktb_sign_ctx_t C_ctx;
		if(ctx != 0) {
			C_ctx = (ktb_sign_ctx_t)((contextWrapper *)ctx)->ctxRef;
			((contextWrapper *)ctx)->env = env;
		}
		else
			C_ctx = NULL;

		 JNI_result = ktb_sign_get_sign_size (C_ctx);

		 return JNI_result;
	}

	JNIEXPORT jbyteArray JNICALL JNI_ktb_sign_get_sign(JNIEnv *env, jclass cls, jlong ctx) {

		jbyteArray JNI_result;

		ktb_sign_ctx_t C_ctx;
		if(ctx != 0) {
			C_ctx = (ktb_sign_ctx_t)((contextWrapper *)ctx)->ctxRef;
			((contextWrapper *)ctx)->env = env;
		}
		else
			C_ctx = NULL;

		size_t C_size;

		void* tempJNI_result = (void*)ktb_sign_get_sign (C_ctx, &C_size);

		JNI_result = (*env)->NewByteArray(env, C_size);
		(*env)->SetByteArrayRegion(env, JNI_result, 0, C_size, (jbyte *)tempJNI_result);
		return JNI_result;
	}

	JNIEXPORT jlong JNICALL JNI_ktb_sign_get_sign_size_from_key(JNIEnv *env, jclass cls, jlong private_key) {

		jlong JNI_result;

		const_ktb_private_key_t C_private_key;
		if(private_key != 0) {
			C_private_key = (const_ktb_private_key_t)((contextWrapper *)private_key)->ctxRef;
			((contextWrapper *)private_key)->env = env;
		}
		else
			C_private_key = NULL;

		 JNI_result = ktb_sign_get_sign_size_from_key (C_private_key);

		 return JNI_result;
	}

	JNIEXPORT jobject JNICALL JNI_ktb_sign_sign_block(JNIEnv *env, jclass cls, jobject algo,jlong prng,jlong private_key,jbyteArray data,jbyteArray signature) {

		jobject JNI_result;

		jclass enm_algo;
		enm_algo = (*env)->GetObjectClass(env, algo);
		jmethodID get_algo = (*env)->GetMethodID(env, enm_algo, "getValue", "()I");
		jint algo_value = (*env)->CallIntMethod(env, algo, get_algo);
		ktb_hash_algo_t C_algo = (ktb_hash_algo_t)algo_value;

		ktb_prng_t C_prng;
		if(prng != 0) {
			C_prng = (ktb_prng_t)((contextWrapper *)prng)->ctxRef;
			((contextWrapper *)prng)->env = env;
		}
		else
			C_prng = NULL;

		const_ktb_private_key_t C_private_key;
		if(private_key != 0) {
			C_private_key = (const_ktb_private_key_t)((contextWrapper *)private_key)->ctxRef;
			((contextWrapper *)private_key)->env = env;
		}
		else
			C_private_key = NULL;

		jbyte * C_data;
		int C_data_size = (*env)->GetArrayLength(env, data);
		C_data = (jbyte *)malloc(C_data_size);
		C_data = (*env)->GetByteArrayElements(env, data, NULL);

		jbyte * C_signature;
		int C_signature_size = (*env)->GetArrayLength(env, signature);
		C_signature = (jbyte *)malloc(C_signature_size);
		C_signature = (*env)->GetByteArrayElements(env, signature, NULL);

		ktb_errno tempJNI_result = ktb_sign_sign_block (C_algo, C_prng, C_private_key, C_data, C_data_size, C_signature, C_signature_size);

		(*env)->SetByteArrayRegion(env, data, 0, C_data_size, C_data);
		int i_C_data;
		for(i_C_data = 0; i_C_data < C_data_size; ++i_C_data)
			C_data[i_C_data] = 0;
		free(C_data);

		(*env)->SetByteArrayRegion(env, signature, 0, C_signature_size, C_signature);
		int i_C_signature;
		for(i_C_signature = 0; i_C_signature < C_signature_size; ++i_C_signature)
			C_signature[i_C_signature] = 0;
		free(C_signature);

		jclass retObjCls = (*env)->FindClass(env, "ArcanaJNI$ktb_errno");
		jmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, "values", "()[LArcanaJNI$ktb_errno;");
		jobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);

		int arrayLength = (*env)->GetArrayLength(env, valuesArray);

		int i, val;
		jmethodID getVal;
		getVal = (*env)->GetMethodID(env, retObjCls, "getValue", "()I");

		for(i = 0; i < arrayLength; ++i)
		{
			JNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);
			val = (*env)->CallIntMethod(env, JNI_result, getVal);
			if(val == tempJNI_result) {
				break;
			}
		}
		return JNI_result;

	}

	JNIEXPORT jobject JNICALL JNI_ktb_kdf(JNIEnv *env, jclass cls, jobject algo,jbyteArray seed,jbyteArray derived_key) {

		jobject JNI_result;

		jclass enm_algo;
		enm_algo = (*env)->GetObjectClass(env, algo);
		jmethodID get_algo = (*env)->GetMethodID(env, enm_algo, "getValue", "()I");
		jint algo_value = (*env)->CallIntMethod(env, algo, get_algo);
		ktb_hash_algo_t C_algo = (ktb_hash_algo_t)algo_value;

		jbyte * C_seed;
		int C_seed_size = (*env)->GetArrayLength(env, seed);
		C_seed = (jbyte *)malloc(C_seed_size);
		C_seed = (*env)->GetByteArrayElements(env, seed, NULL);

		jbyte * C_derived_key;
		int C_derived_key_size = (*env)->GetArrayLength(env, derived_key);
		C_derived_key = (jbyte *)malloc(C_derived_key_size);
		C_derived_key = (*env)->GetByteArrayElements(env, derived_key, NULL);

		ktb_errno tempJNI_result = ktb_kdf (C_algo, C_seed, C_seed_size, C_derived_key, C_derived_key_size);

		(*env)->SetByteArrayRegion(env, seed, 0, C_seed_size, C_seed);
		int i_C_seed;
		for(i_C_seed = 0; i_C_seed < C_seed_size; ++i_C_seed)
			C_seed[i_C_seed] = 0;
		free(C_seed);

		(*env)->SetByteArrayRegion(env, derived_key, 0, C_derived_key_size, C_derived_key);
		int i_C_derived_key;
		for(i_C_derived_key = 0; i_C_derived_key < C_derived_key_size; ++i_C_derived_key)
			C_derived_key[i_C_derived_key] = 0;
		free(C_derived_key);

		jclass retObjCls = (*env)->FindClass(env, "ArcanaJNI$ktb_errno");
		jmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, "values", "()[LArcanaJNI$ktb_errno;");
		jobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);

		int arrayLength = (*env)->GetArrayLength(env, valuesArray);

		int i, val;
		jmethodID getVal;
		getVal = (*env)->GetMethodID(env, retObjCls, "getValue", "()I");

		for(i = 0; i < arrayLength; ++i)
		{
			JNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);
			val = (*env)->CallIntMethod(env, JNI_result, getVal);
			if(val == tempJNI_result) {
				break;
			}
		}
		return JNI_result;

	}

	JNIEXPORT jobject JNICALL JNI_ktb_pbkdf(JNIEnv *env, jclass cls, jobject algo,jbyteArray passwd,jbyteArray salt,jlong iteration_count,jbyteArray derived_key) {

		jobject JNI_result;

		jclass enm_algo;
		enm_algo = (*env)->GetObjectClass(env, algo);
		jmethodID get_algo = (*env)->GetMethodID(env, enm_algo, "getValue", "()I");
		jint algo_value = (*env)->CallIntMethod(env, algo, get_algo);
		ktb_hash_algo_t C_algo = (ktb_hash_algo_t)algo_value;

		jbyte * C_passwd;
		int C_passwd_size = (*env)->GetArrayLength(env, passwd);
		C_passwd = (jbyte *)malloc(C_passwd_size);
		C_passwd = (*env)->GetByteArrayElements(env, passwd, NULL);

		jbyte * C_salt;
		int C_salt_size = (*env)->GetArrayLength(env, salt);
		C_salt = (jbyte *)malloc(C_salt_size);
		C_salt = (*env)->GetByteArrayElements(env, salt, NULL);

		size_t C_iteration_count = (size_t) iteration_count;

		jbyte * C_derived_key;
		int C_derived_key_size = (*env)->GetArrayLength(env, derived_key);
		C_derived_key = (jbyte *)malloc(C_derived_key_size);
		C_derived_key = (*env)->GetByteArrayElements(env, derived_key, NULL);

		ktb_errno tempJNI_result = ktb_pbkdf (C_algo, C_passwd, C_passwd_size, C_salt, C_salt_size, C_iteration_count, C_derived_key, C_derived_key_size);

		(*env)->SetByteArrayRegion(env, passwd, 0, C_passwd_size, C_passwd);
		int i_C_passwd;
		for(i_C_passwd = 0; i_C_passwd < C_passwd_size; ++i_C_passwd)
			C_passwd[i_C_passwd] = 0;
		free(C_passwd);

		(*env)->SetByteArrayRegion(env, salt, 0, C_salt_size, C_salt);
		int i_C_salt;
		for(i_C_salt = 0; i_C_salt < C_salt_size; ++i_C_salt)
			C_salt[i_C_salt] = 0;
		free(C_salt);

		(*env)->SetByteArrayRegion(env, derived_key, 0, C_derived_key_size, C_derived_key);
		int i_C_derived_key;
		for(i_C_derived_key = 0; i_C_derived_key < C_derived_key_size; ++i_C_derived_key)
			C_derived_key[i_C_derived_key] = 0;
		free(C_derived_key);

		jclass retObjCls = (*env)->FindClass(env, "ArcanaJNI$ktb_errno");
		jmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, "values", "()[LArcanaJNI$ktb_errno;");
		jobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);

		int arrayLength = (*env)->GetArrayLength(env, valuesArray);

		int i, val;
		jmethodID getVal;
		getVal = (*env)->GetMethodID(env, retObjCls, "getValue", "()I");

		for(i = 0; i < arrayLength; ++i)
		{
			JNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);
			val = (*env)->CallIntMethod(env, JNI_result, getVal);
			if(val == tempJNI_result) {
				break;
			}
		}
		return JNI_result;

	}

	JNIEXPORT jlong JNICALL JNI_ktb_kdf_max_size(JNIEnv *env, jclass cls, jobject algo) {

		jlong JNI_result;

		jclass enm_algo;
		enm_algo = (*env)->GetObjectClass(env, algo);
		jmethodID get_algo = (*env)->GetMethodID(env, enm_algo, "getValue", "()I");
		jint algo_value = (*env)->CallIntMethod(env, algo, get_algo);
		ktb_hash_algo_t C_algo = (ktb_hash_algo_t)algo_value;

		 JNI_result = ktb_kdf_max_size (C_algo);

		 return JNI_result;
	}

	JNIEXPORT jint JNICALL JNI_ktb_strerror(JNIEnv *env, jclass cls, jobject err,jbyteArray buf) {

		jint JNI_result;

		jclass enm_err;
		enm_err = (*env)->GetObjectClass(env, err);
		jmethodID get_err = (*env)->GetMethodID(env, enm_err, "getValue", "()I");
		jint err_value = (*env)->CallIntMethod(env, err, get_err);
		ktb_errno C_err = (ktb_errno)err_value;

		jbyte * C_buf;
		int C_buf_size = (*env)->GetArrayLength(env, buf);
		C_buf = (jbyte *)malloc(C_buf_size);
		C_buf = (*env)->GetByteArrayElements(env, buf, NULL);

		 JNI_result = ktb_strerror (C_err, C_buf, C_buf_size);

		(*env)->SetByteArrayRegion(env, buf, 0, C_buf_size, C_buf);
		int i_C_buf;
		for(i_C_buf = 0; i_C_buf < C_buf_size; ++i_C_buf)
			C_buf[i_C_buf] = 0;
		free(C_buf);

		 return JNI_result;
	}

	JNIEXPORT jlong JNICALL JNI_ktb_kem_psec_encrypt_size(JNIEnv *env, jclass cls, jlong peer_public_key) {

		jlong JNI_result;

		const_ktb_public_key_t C_peer_public_key;
		if(peer_public_key != 0) {
			C_peer_public_key = (const_ktb_public_key_t)((contextWrapper *)peer_public_key)->ctxRef;
			((contextWrapper *)peer_public_key)->env = env;
		}
		else
			C_peer_public_key = NULL;

		 JNI_result = ktb_kem_psec_encrypt_size (C_peer_public_key);

		 return JNI_result;
	}

	JNIEXPORT jobject JNICALL JNI_ktb_kem_psec_encrypt(JNIEnv *env, jclass cls, jobject algo,jlong prng,jlong peer_public_key,jbyteArray secret_key,jbyteArray ciphertext) {

		jobject JNI_result;

		jclass enm_algo;
		enm_algo = (*env)->GetObjectClass(env, algo);
		jmethodID get_algo = (*env)->GetMethodID(env, enm_algo, "getValue", "()I");
		jint algo_value = (*env)->CallIntMethod(env, algo, get_algo);
		ktb_hash_algo_t C_algo = (ktb_hash_algo_t)algo_value;

		ktb_prng_t C_prng;
		if(prng != 0) {
			C_prng = (ktb_prng_t)((contextWrapper *)prng)->ctxRef;
			((contextWrapper *)prng)->env = env;
		}
		else
			C_prng = NULL;

		const_ktb_public_key_t C_peer_public_key;
		if(peer_public_key != 0) {
			C_peer_public_key = (const_ktb_public_key_t)((contextWrapper *)peer_public_key)->ctxRef;
			((contextWrapper *)peer_public_key)->env = env;
		}
		else
			C_peer_public_key = NULL;

		jbyte * C_secret_key;
		int C_secret_key_size = (*env)->GetArrayLength(env, secret_key);
		C_secret_key = (jbyte *)malloc(C_secret_key_size);
		C_secret_key = (*env)->GetByteArrayElements(env, secret_key, NULL);

		jbyte * C_ciphertext;
		int C_ciphertext_size = (*env)->GetArrayLength(env, ciphertext);
		C_ciphertext = (jbyte *)malloc(C_ciphertext_size);
		C_ciphertext = (*env)->GetByteArrayElements(env, ciphertext, NULL);

		ktb_errno tempJNI_result = ktb_kem_psec_encrypt (C_algo, C_prng, C_peer_public_key, C_secret_key, C_secret_key_size, C_ciphertext, C_ciphertext_size);

		(*env)->SetByteArrayRegion(env, secret_key, 0, C_secret_key_size, C_secret_key);
		int i_C_secret_key;
		for(i_C_secret_key = 0; i_C_secret_key < C_secret_key_size; ++i_C_secret_key)
			C_secret_key[i_C_secret_key] = 0;
		free(C_secret_key);

		(*env)->SetByteArrayRegion(env, ciphertext, 0, C_ciphertext_size, C_ciphertext);
		int i_C_ciphertext;
		for(i_C_ciphertext = 0; i_C_ciphertext < C_ciphertext_size; ++i_C_ciphertext)
			C_ciphertext[i_C_ciphertext] = 0;
		free(C_ciphertext);

		jclass retObjCls = (*env)->FindClass(env, "ArcanaJNI$ktb_errno");
		jmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, "values", "()[LArcanaJNI$ktb_errno;");
		jobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);

		int arrayLength = (*env)->GetArrayLength(env, valuesArray);

		int i, val;
		jmethodID getVal;
		getVal = (*env)->GetMethodID(env, retObjCls, "getValue", "()I");

		for(i = 0; i < arrayLength; ++i)
		{
			JNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);
			val = (*env)->CallIntMethod(env, JNI_result, getVal);
			if(val == tempJNI_result) {
				break;
			}
		}
		return JNI_result;

	}

	JNIEXPORT jobject JNICALL JNI_ktb_kem_psec_decrypt(JNIEnv *env, jclass cls, jobject algo,jlong self_private_key,jbyteArray input_ciphertext,jbyteArray secret_key) {

		jobject JNI_result;

		jclass enm_algo;
		enm_algo = (*env)->GetObjectClass(env, algo);
		jmethodID get_algo = (*env)->GetMethodID(env, enm_algo, "getValue", "()I");
		jint algo_value = (*env)->CallIntMethod(env, algo, get_algo);
		ktb_hash_algo_t C_algo = (ktb_hash_algo_t)algo_value;

		const_ktb_private_key_t C_self_private_key;
		if(self_private_key != 0) {
			C_self_private_key = (const_ktb_private_key_t)((contextWrapper *)self_private_key)->ctxRef;
			((contextWrapper *)self_private_key)->env = env;
		}
		else
			C_self_private_key = NULL;

		jbyte * C_input_ciphertext;
		int C_input_ciphertext_size = (*env)->GetArrayLength(env, input_ciphertext);
		C_input_ciphertext = (jbyte *)malloc(C_input_ciphertext_size);
		C_input_ciphertext = (*env)->GetByteArrayElements(env, input_ciphertext, NULL);

		jbyte * C_secret_key;
		int C_secret_key_size = (*env)->GetArrayLength(env, secret_key);
		C_secret_key = (jbyte *)malloc(C_secret_key_size);
		C_secret_key = (*env)->GetByteArrayElements(env, secret_key, NULL);

		ktb_errno tempJNI_result = ktb_kem_psec_decrypt (C_algo, C_self_private_key, C_input_ciphertext, C_input_ciphertext_size, C_secret_key, C_secret_key_size);

		(*env)->SetByteArrayRegion(env, input_ciphertext, 0, C_input_ciphertext_size, C_input_ciphertext);
		int i_C_input_ciphertext;
		for(i_C_input_ciphertext = 0; i_C_input_ciphertext < C_input_ciphertext_size; ++i_C_input_ciphertext)
			C_input_ciphertext[i_C_input_ciphertext] = 0;
		free(C_input_ciphertext);

		(*env)->SetByteArrayRegion(env, secret_key, 0, C_secret_key_size, C_secret_key);
		int i_C_secret_key;
		for(i_C_secret_key = 0; i_C_secret_key < C_secret_key_size; ++i_C_secret_key)
			C_secret_key[i_C_secret_key] = 0;
		free(C_secret_key);

		jclass retObjCls = (*env)->FindClass(env, "ArcanaJNI$ktb_errno");
		jmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, "values", "()[LArcanaJNI$ktb_errno;");
		jobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);

		int arrayLength = (*env)->GetArrayLength(env, valuesArray);

		int i, val;
		jmethodID getVal;
		getVal = (*env)->GetMethodID(env, retObjCls, "getValue", "()I");

		for(i = 0; i < arrayLength; ++i)
		{
			JNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);
			val = (*env)->CallIntMethod(env, JNI_result, getVal);
			if(val == tempJNI_result) {
				break;
			}
		}
		return JNI_result;

	}

	JNIEXPORT void JNICALL JNI_ktb_prng_clear(JNIEnv *env, jclass cls, jlong prng) {

		ktb_prng_t C_prng;
		if(prng != 0) {
			C_prng = (ktb_prng_t)((contextWrapper *)prng)->ctxRef;
			((contextWrapper *)prng)->env = env;
		}
		else
			C_prng = NULL;

		  ktb_prng_clear (C_prng);

	}

	JNIEXPORT jobject JNICALL JNI_ktb_prng_reseed_with(JNIEnv *env, jclass cls, jlong prng,jbyteArray buffer) {

		jobject JNI_result;

		ktb_prng_t C_prng;
		if(prng != 0) {
			C_prng = (ktb_prng_t)((contextWrapper *)prng)->ctxRef;
			((contextWrapper *)prng)->env = env;
		}
		else
			C_prng = NULL;

		jbyte * C_buffer;
		int C_buffer_size = (*env)->GetArrayLength(env, buffer);
		C_buffer = (jbyte *)malloc(C_buffer_size);
		C_buffer = (*env)->GetByteArrayElements(env, buffer, NULL);

		ktb_errno tempJNI_result = ktb_prng_reseed_with (C_prng, C_buffer, C_buffer_size);

		(*env)->SetByteArrayRegion(env, buffer, 0, C_buffer_size, C_buffer);
		int i_C_buffer;
		for(i_C_buffer = 0; i_C_buffer < C_buffer_size; ++i_C_buffer)
			C_buffer[i_C_buffer] = 0;
		free(C_buffer);

		jclass retObjCls = (*env)->FindClass(env, "ArcanaJNI$ktb_errno");
		jmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, "values", "()[LArcanaJNI$ktb_errno;");
		jobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);

		int arrayLength = (*env)->GetArrayLength(env, valuesArray);

		int i, val;
		jmethodID getVal;
		getVal = (*env)->GetMethodID(env, retObjCls, "getValue", "()I");

		for(i = 0; i < arrayLength; ++i)
		{
			JNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);
			val = (*env)->CallIntMethod(env, JNI_result, getVal);
			if(val == tempJNI_result) {
				break;
			}
		}
		return JNI_result;

	}

	JNIEXPORT jobject JNICALL JNI_ktb_prng_reseed(JNIEnv *env, jclass cls, jlong prng) {

		jobject JNI_result;

		ktb_prng_t C_prng;
		if(prng != 0) {
			C_prng = (ktb_prng_t)((contextWrapper *)prng)->ctxRef;
			((contextWrapper *)prng)->env = env;
		}
		else
			C_prng = NULL;

		ktb_errno tempJNI_result = ktb_prng_reseed (C_prng);

		jclass retObjCls = (*env)->FindClass(env, "ArcanaJNI$ktb_errno");
		jmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, "values", "()[LArcanaJNI$ktb_errno;");
		jobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);

		int arrayLength = (*env)->GetArrayLength(env, valuesArray);

		int i, val;
		jmethodID getVal;
		getVal = (*env)->GetMethodID(env, retObjCls, "getValue", "()I");

		for(i = 0; i < arrayLength; ++i)
		{
			JNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);
			val = (*env)->CallIntMethod(env, JNI_result, getVal);
			if(val == tempJNI_result) {
				break;
			}
		}
		return JNI_result;

	}

	JNIEXPORT jobject JNICALL JNI_ktb_prng_fill_buffer(JNIEnv *env, jclass cls, jlong prng,jbyteArray buffer) {

		jobject JNI_result;

		ktb_prng_t C_prng;
		if(prng != 0) {
			C_prng = (ktb_prng_t)((contextWrapper *)prng)->ctxRef;
			((contextWrapper *)prng)->env = env;
		}
		else
			C_prng = NULL;

		jbyte * C_buffer;
		int C_buffer_size = (*env)->GetArrayLength(env, buffer);
		C_buffer = (jbyte *)malloc(C_buffer_size);
		C_buffer = (*env)->GetByteArrayElements(env, buffer, NULL);

		ktb_errno tempJNI_result = ktb_prng_fill_buffer (C_prng, C_buffer, C_buffer_size);

		(*env)->SetByteArrayRegion(env, buffer, 0, C_buffer_size, C_buffer);
		int i_C_buffer;
		for(i_C_buffer = 0; i_C_buffer < C_buffer_size; ++i_C_buffer)
			C_buffer[i_C_buffer] = 0;
		free(C_buffer);

		jclass retObjCls = (*env)->FindClass(env, "ArcanaJNI$ktb_errno");
		jmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, "values", "()[LArcanaJNI$ktb_errno;");
		jobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);

		int arrayLength = (*env)->GetArrayLength(env, valuesArray);

		int i, val;
		jmethodID getVal;
		getVal = (*env)->GetMethodID(env, retObjCls, "getValue", "()I");

		for(i = 0; i < arrayLength; ++i)
		{
			JNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);
			val = (*env)->CallIntMethod(env, JNI_result, getVal);
			if(val == tempJNI_result) {
				break;
			}
		}
		return JNI_result;

	}

	JNIEXPORT void JNICALL JNI_ktb_keys_public_key_clear(JNIEnv *env, jclass cls, jlong key) {

		ktb_public_key_t C_key;
		if(key != 0) {
			C_key = (ktb_public_key_t)((contextWrapper *)key)->ctxRef;
			((contextWrapper *)key)->env = env;
		}
		else
			C_key = NULL;

		  ktb_keys_public_key_clear (C_key);

	}

	JNIEXPORT void JNICALL JNI_ktb_keys_private_key_clear(JNIEnv *env, jclass cls, jlong key) {

		ktb_private_key_t C_key;
		if(key != 0) {
			C_key = (ktb_private_key_t)((contextWrapper *)key)->ctxRef;
			((contextWrapper *)key)->env = env;
		}
		else
			C_key = NULL;

		  ktb_keys_private_key_clear (C_key);

	}

	JNIEXPORT jlong JNICALL JNI_ktb_keys_public_key_export_size(JNIEnv *env, jclass cls, jlong public_key) {

		jlong JNI_result;

		const_ktb_public_key_t C_public_key;
		if(public_key != 0) {
			C_public_key = (const_ktb_public_key_t)((contextWrapper *)public_key)->ctxRef;
			((contextWrapper *)public_key)->env = env;
		}
		else
			C_public_key = NULL;

		 JNI_result = ktb_keys_public_key_export_size (C_public_key);

		 return JNI_result;
	}

	JNIEXPORT jobject JNICALL JNI_ktb_keys_public_key_export(JNIEnv *env, jclass cls, jlong public_key,jbyteArray result) {

		jobject JNI_result;

		const_ktb_public_key_t C_public_key;
		if(public_key != 0) {
			C_public_key = (const_ktb_public_key_t)((contextWrapper *)public_key)->ctxRef;
			((contextWrapper *)public_key)->env = env;
		}
		else
			C_public_key = NULL;

		jbyte * C_result;
		int C_result_size = (*env)->GetArrayLength(env, result);
		C_result = (jbyte *)malloc(C_result_size);
		C_result = (*env)->GetByteArrayElements(env, result, NULL);

		ktb_errno tempJNI_result = ktb_keys_public_key_export (C_public_key, C_result, C_result_size);

		(*env)->SetByteArrayRegion(env, result, 0, C_result_size, C_result);
		int i_C_result;
		for(i_C_result = 0; i_C_result < C_result_size; ++i_C_result)
			C_result[i_C_result] = 0;
		free(C_result);

		jclass retObjCls = (*env)->FindClass(env, "ArcanaJNI$ktb_errno");
		jmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, "values", "()[LArcanaJNI$ktb_errno;");
		jobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);

		int arrayLength = (*env)->GetArrayLength(env, valuesArray);

		int i, val;
		jmethodID getVal;
		getVal = (*env)->GetMethodID(env, retObjCls, "getValue", "()I");

		for(i = 0; i < arrayLength; ++i)
		{
			JNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);
			val = (*env)->CallIntMethod(env, JNI_result, getVal);
			if(val == tempJNI_result) {
				break;
			}
		}
		return JNI_result;

	}

	JNIEXPORT jobject JNICALL JNI_ktb_keys_public_key_import(JNIEnv *env, jclass cls, jbyteArray public_key_bytes,jobject public_key) {

		jobject JNI_result;

		jbyte * C_public_key_bytes;
		int C_public_key_bytes_size = (*env)->GetArrayLength(env, public_key_bytes);
		C_public_key_bytes = (jbyte *)malloc(C_public_key_bytes_size);
		C_public_key_bytes = (*env)->GetByteArrayElements(env, public_key_bytes, NULL);

		ktb_public_key_t C_public_key;
		contextWrapper *ctxWrp1 = (contextWrapper *)malloc(sizeof(contextWrapper));
		ctxWrp1->env = env;

		ktb_errno tempJNI_result = ktb_keys_public_key_import (C_public_key_bytes, C_public_key_bytes_size, &C_public_key);

		(*env)->SetByteArrayRegion(env, public_key_bytes, 0, C_public_key_bytes_size, C_public_key_bytes);
		int i_C_public_key_bytes;
		for(i_C_public_key_bytes = 0; i_C_public_key_bytes < C_public_key_bytes_size; ++i_C_public_key_bytes)
			C_public_key_bytes[i_C_public_key_bytes] = 0;
		free(C_public_key_bytes);

		ctxWrp1->ctxRef = C_public_key;
		jclass adrWrp_public_key;
		jmethodID setAddr_public_key;
		jlong arg_public_key;

		adrWrp_public_key = (*env)->GetObjectClass(env, public_key);
		setAddr_public_key = (*env)->GetMethodID(env, adrWrp_public_key, "setAddress", "(J)V");
		arg_public_key = (jlong) ctxWrp1;
		(*env)->CallVoidMethod(env, public_key, setAddr_public_key, arg_public_key);

		jclass retObjCls = (*env)->FindClass(env, "ArcanaJNI$ktb_errno");
		jmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, "values", "()[LArcanaJNI$ktb_errno;");
		jobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);

		int arrayLength = (*env)->GetArrayLength(env, valuesArray);

		int i, val;
		jmethodID getVal;
		getVal = (*env)->GetMethodID(env, retObjCls, "getValue", "()I");

		for(i = 0; i < arrayLength; ++i)
		{
			JNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);
			val = (*env)->CallIntMethod(env, JNI_result, getVal);
			if(val == tempJNI_result) {
				break;
			}
		}
		return JNI_result;

	}

	JNIEXPORT jlong JNICALL JNI_ktb_keys_private_key_export_size(JNIEnv *env, jclass cls, jlong key) {

		jlong JNI_result;

		const_ktb_private_key_t C_key;
		if(key != 0) {
			C_key = (const_ktb_private_key_t)((contextWrapper *)key)->ctxRef;
			((contextWrapper *)key)->env = env;
		}
		else
			C_key = NULL;

		 JNI_result = ktb_keys_private_key_export_size (C_key);

		 return JNI_result;
	}

	JNIEXPORT jobject JNICALL JNI_ktb_keys_private_key_export(JNIEnv *env, jclass cls, jlong key,jbyteArray buffer) {

		jobject JNI_result;

		const_ktb_private_key_t C_key;
		if(key != 0) {
			C_key = (const_ktb_private_key_t)((contextWrapper *)key)->ctxRef;
			((contextWrapper *)key)->env = env;
		}
		else
			C_key = NULL;

		jbyte * C_buffer;
		int C_buffer_size = (*env)->GetArrayLength(env, buffer);
		C_buffer = (jbyte *)malloc(C_buffer_size);
		C_buffer = (*env)->GetByteArrayElements(env, buffer, NULL);

		ktb_errno tempJNI_result = ktb_keys_private_key_export (C_key, C_buffer, C_buffer_size);

		(*env)->SetByteArrayRegion(env, buffer, 0, C_buffer_size, C_buffer);
		int i_C_buffer;
		for(i_C_buffer = 0; i_C_buffer < C_buffer_size; ++i_C_buffer)
			C_buffer[i_C_buffer] = 0;
		free(C_buffer);

		jclass retObjCls = (*env)->FindClass(env, "ArcanaJNI$ktb_errno");
		jmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, "values", "()[LArcanaJNI$ktb_errno;");
		jobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);

		int arrayLength = (*env)->GetArrayLength(env, valuesArray);

		int i, val;
		jmethodID getVal;
		getVal = (*env)->GetMethodID(env, retObjCls, "getValue", "()I");

		for(i = 0; i < arrayLength; ++i)
		{
			JNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);
			val = (*env)->CallIntMethod(env, JNI_result, getVal);
			if(val == tempJNI_result) {
				break;
			}
		}
		return JNI_result;

	}

	JNIEXPORT jobject JNICALL JNI_ktb_keys_private_key_import(JNIEnv *env, jclass cls, jbyteArray private_key_bytes,jobject private_key) {

		jobject JNI_result;

		jbyte * C_private_key_bytes;
		int C_private_key_bytes_size = (*env)->GetArrayLength(env, private_key_bytes);
		C_private_key_bytes = (jbyte *)malloc(C_private_key_bytes_size);
		C_private_key_bytes = (*env)->GetByteArrayElements(env, private_key_bytes, NULL);

		ktb_private_key_t C_private_key;
		contextWrapper *ctxWrp1 = (contextWrapper *)malloc(sizeof(contextWrapper));
		ctxWrp1->env = env;

		ktb_errno tempJNI_result = ktb_keys_private_key_import (C_private_key_bytes, C_private_key_bytes_size, &C_private_key);

		(*env)->SetByteArrayRegion(env, private_key_bytes, 0, C_private_key_bytes_size, C_private_key_bytes);
		int i_C_private_key_bytes;
		for(i_C_private_key_bytes = 0; i_C_private_key_bytes < C_private_key_bytes_size; ++i_C_private_key_bytes)
			C_private_key_bytes[i_C_private_key_bytes] = 0;
		free(C_private_key_bytes);

		ctxWrp1->ctxRef = C_private_key;
		jclass adrWrp_private_key;
		jmethodID setAddr_private_key;
		jlong arg_private_key;

		adrWrp_private_key = (*env)->GetObjectClass(env, private_key);
		setAddr_private_key = (*env)->GetMethodID(env, adrWrp_private_key, "setAddress", "(J)V");
		arg_private_key = (jlong) ctxWrp1;
		(*env)->CallVoidMethod(env, private_key, setAddr_private_key, arg_private_key);

		jclass retObjCls = (*env)->FindClass(env, "ArcanaJNI$ktb_errno");
		jmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, "values", "()[LArcanaJNI$ktb_errno;");
		jobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);

		int arrayLength = (*env)->GetArrayLength(env, valuesArray);

		int i, val;
		jmethodID getVal;
		getVal = (*env)->GetMethodID(env, retObjCls, "getValue", "()I");

		for(i = 0; i < arrayLength; ++i)
		{
			JNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);
			val = (*env)->CallIntMethod(env, JNI_result, getVal);
			if(val == tempJNI_result) {
				break;
			}
		}
		return JNI_result;

	}

	JNIEXPORT jobject JNICALL JNI_ktb_keys_generate_keypair(JNIEnv *env, jclass cls, jlong prng,jstring curve_id,jobject public_key,jobject private_key) {

		jobject JNI_result;

		ktb_prng_t C_prng;
		if(prng != 0) {
			C_prng = (ktb_prng_t)((contextWrapper *)prng)->ctxRef;
			((contextWrapper *)prng)->env = env;
		}
		else
			C_prng = NULL;

		char * C_curve_id;
		C_curve_id = (char *)(*env)->GetStringUTFChars(env, curve_id, NULL);
		if(C_curve_id == NULL) {
			 fprintf(stderr, " Out of memory");
			 exit(1);
		}

		ktb_public_key_t C_public_key;
		contextWrapper *ctxWrp2 = (contextWrapper *)malloc(sizeof(contextWrapper));
		ctxWrp2->env = env;

		ktb_private_key_t C_private_key;
		contextWrapper *ctxWrp3 = (contextWrapper *)malloc(sizeof(contextWrapper));
		ctxWrp3->env = env;

		ktb_errno tempJNI_result = ktb_keys_generate_keypair (C_prng, C_curve_id, &C_public_key, &C_private_key);

		ctxWrp2->ctxRef = C_public_key;
		jclass adrWrp_public_key;
		jmethodID setAddr_public_key;
		jlong arg_public_key;

		adrWrp_public_key = (*env)->GetObjectClass(env, public_key);
		setAddr_public_key = (*env)->GetMethodID(env, adrWrp_public_key, "setAddress", "(J)V");
		arg_public_key = (jlong) ctxWrp2;
		(*env)->CallVoidMethod(env, public_key, setAddr_public_key, arg_public_key);

		ctxWrp3->ctxRef = C_private_key;
		jclass adrWrp_private_key;
		jmethodID setAddr_private_key;
		jlong arg_private_key;

		adrWrp_private_key = (*env)->GetObjectClass(env, private_key);
		setAddr_private_key = (*env)->GetMethodID(env, adrWrp_private_key, "setAddress", "(J)V");
		arg_private_key = (jlong) ctxWrp3;
		(*env)->CallVoidMethod(env, private_key, setAddr_private_key, arg_private_key);

		jclass retObjCls = (*env)->FindClass(env, "ArcanaJNI$ktb_errno");
		jmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, "values", "()[LArcanaJNI$ktb_errno;");
		jobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);

		int arrayLength = (*env)->GetArrayLength(env, valuesArray);

		int i, val;
		jmethodID getVal;
		getVal = (*env)->GetMethodID(env, retObjCls, "getValue", "()I");

		for(i = 0; i < arrayLength; ++i)
		{
			JNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);
			val = (*env)->CallIntMethod(env, JNI_result, getVal);
			if(val == tempJNI_result) {
				break;
			}
		}
		return JNI_result;

	}

	JNIEXPORT jlong JNICALL JNI_ktb_radix64_encode_size(JNIEnv *env, jclass cls, jlong input_size) {

		jlong JNI_result;

		size_t C_input_size = (size_t) input_size;

		 JNI_result = ktb_radix64_encode_size (C_input_size);

		 return JNI_result;
	}

	JNIEXPORT jobject JNICALL JNI_ktb_radix64_encode(JNIEnv *env, jclass cls, jbyteArray input,jbyteArray result) {

		jobject JNI_result;

		jbyte * C_input;
		int C_input_size = (*env)->GetArrayLength(env, input);
		C_input = (jbyte *)malloc(C_input_size);
		C_input = (*env)->GetByteArrayElements(env, input, NULL);

		jbyte * C_result;
		int C_result_size = (*env)->GetArrayLength(env, result);
		C_result = (jbyte *)malloc(C_result_size);
		C_result = (*env)->GetByteArrayElements(env, result, NULL);

		ktb_errno tempJNI_result = ktb_radix64_encode (C_input, C_input_size, C_result, C_result_size);

		(*env)->SetByteArrayRegion(env, input, 0, C_input_size, C_input);
		int i_C_input;
		for(i_C_input = 0; i_C_input < C_input_size; ++i_C_input)
			C_input[i_C_input] = 0;
		free(C_input);

		(*env)->SetByteArrayRegion(env, result, 0, C_result_size, C_result);
		int i_C_result;
		for(i_C_result = 0; i_C_result < C_result_size; ++i_C_result)
			C_result[i_C_result] = 0;
		free(C_result);

		jclass retObjCls = (*env)->FindClass(env, "ArcanaJNI$ktb_errno");
		jmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, "values", "()[LArcanaJNI$ktb_errno;");
		jobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);

		int arrayLength = (*env)->GetArrayLength(env, valuesArray);

		int i, val;
		jmethodID getVal;
		getVal = (*env)->GetMethodID(env, retObjCls, "getValue", "()I");

		for(i = 0; i < arrayLength; ++i)
		{
			JNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);
			val = (*env)->CallIntMethod(env, JNI_result, getVal);
			if(val == tempJNI_result) {
				break;
			}
		}
		return JNI_result;

	}

	JNIEXPORT jlong JNICALL JNI_ktb_radix64_decode_size(JNIEnv *env, jclass cls, jbyteArray input) {

		jlong JNI_result;

		jbyte * C_input;
		int C_input_size = (*env)->GetArrayLength(env, input);
		C_input = (jbyte *)malloc(C_input_size);
		C_input = (*env)->GetByteArrayElements(env, input, NULL);

		 JNI_result = ktb_radix64_decode_size (C_input, C_input_size);

		(*env)->SetByteArrayRegion(env, input, 0, C_input_size, C_input);
		int i_C_input;
		for(i_C_input = 0; i_C_input < C_input_size; ++i_C_input)
			C_input[i_C_input] = 0;
		free(C_input);

		 return JNI_result;
	}

	JNIEXPORT jobject JNICALL JNI_ktb_radix64_decode(JNIEnv *env, jclass cls, jbyteArray input,jbyteArray result) {

		jobject JNI_result;

		jbyte * C_input;
		int C_input_size = (*env)->GetArrayLength(env, input);
		C_input = (jbyte *)malloc(C_input_size);
		C_input = (*env)->GetByteArrayElements(env, input, NULL);

		jbyte * C_result;
		int C_result_size = (*env)->GetArrayLength(env, result);
		C_result = (jbyte *)malloc(C_result_size);
		C_result = (*env)->GetByteArrayElements(env, result, NULL);

		ktb_errno tempJNI_result = ktb_radix64_decode (C_input, C_input_size, C_result, C_result_size);

		(*env)->SetByteArrayRegion(env, input, 0, C_input_size, C_input);
		int i_C_input;
		for(i_C_input = 0; i_C_input < C_input_size; ++i_C_input)
			C_input[i_C_input] = 0;
		free(C_input);

		(*env)->SetByteArrayRegion(env, result, 0, C_result_size, C_result);
		int i_C_result;
		for(i_C_result = 0; i_C_result < C_result_size; ++i_C_result)
			C_result[i_C_result] = 0;
		free(C_result);

		jclass retObjCls = (*env)->FindClass(env, "ArcanaJNI$ktb_errno");
		jmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, "values", "()[LArcanaJNI$ktb_errno;");
		jobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);

		int arrayLength = (*env)->GetArrayLength(env, valuesArray);

		int i, val;
		jmethodID getVal;
		getVal = (*env)->GetMethodID(env, retObjCls, "getValue", "()I");

		for(i = 0; i < arrayLength; ++i)
		{
			JNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);
			val = (*env)->CallIntMethod(env, JNI_result, getVal);
			if(val == tempJNI_result) {
				break;
			}
		}
		return JNI_result;

	}

	JNIEXPORT jobject JNICALL JNI_ktb_radix64_verify(JNIEnv *env, jclass cls, jbyteArray input,jobject verified) {

		jobject JNI_result;

		jbyte * C_input;
		int C_input_size = (*env)->GetArrayLength(env, input);
		C_input = (jbyte *)malloc(C_input_size);
		C_input = (*env)->GetByteArrayElements(env, input, NULL);

		bool C_verified;

		ktb_errno tempJNI_result = ktb_radix64_verify (C_input, C_input_size, &C_verified);

		(*env)->SetByteArrayRegion(env, input, 0, C_input_size, C_input);
		int i_C_input;
		for(i_C_input = 0; i_C_input < C_input_size; ++i_C_input)
			C_input[i_C_input] = 0;
		free(C_input);

		jclass boolWrp;
		jmethodID setVal;
		jboolean arg;
		boolWrp = (*env)->GetObjectClass(env, verified);
		setVal = (*env)->GetMethodID(env, boolWrp, "setValue", "(Z)V");
		arg = (jboolean) C_verified;
		(*env)->CallVoidMethod(env, verified, setVal, arg);

		jclass retObjCls = (*env)->FindClass(env, "ArcanaJNI$ktb_errno");
		jmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, "values", "()[LArcanaJNI$ktb_errno;");
		jobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);

		int arrayLength = (*env)->GetArrayLength(env, valuesArray);

		int i, val;
		jmethodID getVal;
		getVal = (*env)->GetMethodID(env, retObjCls, "getValue", "()I");

		for(i = 0; i < arrayLength; ++i)
		{
			JNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);
			val = (*env)->CallIntMethod(env, JNI_result, getVal);
			if(val == tempJNI_result) {
				break;
			}
		}
		return JNI_result;

	}

	JNIEXPORT jobject JNICALL JNI_ktb_cipher_init(JNIEnv *env, jclass cls, jobject ctx,jobject algo,jobject mode,jboolean encryption) {

		jobject JNI_result;

		ktb_cipher_ctx_t C_ctx;
		contextWrapper *ctxWrp1 = (contextWrapper *)malloc(sizeof(contextWrapper));
		ctxWrp1->env = env;

		jclass enm_algo;
		enm_algo = (*env)->GetObjectClass(env, algo);
		jmethodID get_algo = (*env)->GetMethodID(env, enm_algo, "getValue", "()I");
		jint algo_value = (*env)->CallIntMethod(env, algo, get_algo);
		ktb_cipher_algo_t C_algo = (ktb_cipher_algo_t)algo_value;

		jclass enm_mode;
		enm_mode = (*env)->GetObjectClass(env, mode);
		jmethodID get_mode = (*env)->GetMethodID(env, enm_mode, "getValue", "()I");
		jint mode_value = (*env)->CallIntMethod(env, mode, get_mode);
		ktb_cipher_mode_t C_mode = (ktb_cipher_mode_t)mode_value;

		bool C_encryption = (bool) encryption;

		ktb_errno tempJNI_result = ktb_cipher_init (&C_ctx, C_algo, C_mode, C_encryption);

		ctxWrp1->ctxRef = C_ctx;
		jclass adrWrp_ctx;
		jmethodID setAddr_ctx;
		jlong arg_ctx;

		adrWrp_ctx = (*env)->GetObjectClass(env, ctx);
		setAddr_ctx = (*env)->GetMethodID(env, adrWrp_ctx, "setAddress", "(J)V");
		arg_ctx = (jlong) ctxWrp1;
		(*env)->CallVoidMethod(env, ctx, setAddr_ctx, arg_ctx);

		jclass retObjCls = (*env)->FindClass(env, "ArcanaJNI$ktb_errno");
		jmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, "values", "()[LArcanaJNI$ktb_errno;");
		jobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);

		int arrayLength = (*env)->GetArrayLength(env, valuesArray);

		int i, val;
		jmethodID getVal;
		getVal = (*env)->GetMethodID(env, retObjCls, "getValue", "()I");

		for(i = 0; i < arrayLength; ++i)
		{
			JNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);
			val = (*env)->CallIntMethod(env, JNI_result, getVal);
			if(val == tempJNI_result) {
				break;
			}
		}
		return JNI_result;

	}

	JNIEXPORT void JNICALL JNI_ktb_cipher_clear(JNIEnv *env, jclass cls, jlong ctx) {

		ktb_cipher_ctx_t C_ctx;
		if(ctx != 0) {
			C_ctx = (ktb_cipher_ctx_t)((contextWrapper *)ctx)->ctxRef;
			((contextWrapper *)ctx)->env = env;
		}
		else
			C_ctx = NULL;

		  ktb_cipher_clear (C_ctx);

	}

	JNIEXPORT void JNICALL JNI_ktb_cipher_reset(JNIEnv *env, jclass cls, jlong ctx) {

		ktb_cipher_ctx_t C_ctx;
		if(ctx != 0) {
			C_ctx = (ktb_cipher_ctx_t)((contextWrapper *)ctx)->ctxRef;
			((contextWrapper *)ctx)->env = env;
		}
		else
			C_ctx = NULL;

		  ktb_cipher_reset (C_ctx);

	}

	JNIEXPORT jobject JNICALL JNI_ktb_cipher_set_key(JNIEnv *env, jclass cls, jlong ctx,jbyteArray key) {

		jobject JNI_result;

		ktb_cipher_ctx_t C_ctx;
		if(ctx != 0) {
			C_ctx = (ktb_cipher_ctx_t)((contextWrapper *)ctx)->ctxRef;
			((contextWrapper *)ctx)->env = env;
		}
		else
			C_ctx = NULL;

		jbyte * C_key;
		int C_key_size = (*env)->GetArrayLength(env, key);
		C_key = (jbyte *)malloc(C_key_size);
		C_key = (*env)->GetByteArrayElements(env, key, NULL);

		ktb_errno tempJNI_result = ktb_cipher_set_key (C_ctx, C_key, C_key_size);

		(*env)->SetByteArrayRegion(env, key, 0, C_key_size, C_key);
		int i_C_key;
		for(i_C_key = 0; i_C_key < C_key_size; ++i_C_key)
			C_key[i_C_key] = 0;
		free(C_key);

		jclass retObjCls = (*env)->FindClass(env, "ArcanaJNI$ktb_errno");
		jmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, "values", "()[LArcanaJNI$ktb_errno;");
		jobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);

		int arrayLength = (*env)->GetArrayLength(env, valuesArray);

		int i, val;
		jmethodID getVal;
		getVal = (*env)->GetMethodID(env, retObjCls, "getValue", "()I");

		for(i = 0; i < arrayLength; ++i)
		{
			JNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);
			val = (*env)->CallIntMethod(env, JNI_result, getVal);
			if(val == tempJNI_result) {
				break;
			}
		}
		return JNI_result;

	}

	JNIEXPORT jobject JNICALL JNI_ktb_cipher_set_iv(JNIEnv *env, jclass cls, jlong ctx,jbyteArray iv) {

		jobject JNI_result;

		ktb_cipher_ctx_t C_ctx;
		if(ctx != 0) {
			C_ctx = (ktb_cipher_ctx_t)((contextWrapper *)ctx)->ctxRef;
			((contextWrapper *)ctx)->env = env;
		}
		else
			C_ctx = NULL;

		jbyte * C_iv;
		int C_iv_size = (*env)->GetArrayLength(env, iv);
		C_iv = (jbyte *)malloc(C_iv_size);
		C_iv = (*env)->GetByteArrayElements(env, iv, NULL);

		ktb_errno tempJNI_result = ktb_cipher_set_iv (C_ctx, C_iv, C_iv_size);

		(*env)->SetByteArrayRegion(env, iv, 0, C_iv_size, C_iv);
		int i_C_iv;
		for(i_C_iv = 0; i_C_iv < C_iv_size; ++i_C_iv)
			C_iv[i_C_iv] = 0;
		free(C_iv);

		jclass retObjCls = (*env)->FindClass(env, "ArcanaJNI$ktb_errno");
		jmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, "values", "()[LArcanaJNI$ktb_errno;");
		jobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);

		int arrayLength = (*env)->GetArrayLength(env, valuesArray);

		int i, val;
		jmethodID getVal;
		getVal = (*env)->GetMethodID(env, retObjCls, "getValue", "()I");

		for(i = 0; i < arrayLength; ++i)
		{
			JNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);
			val = (*env)->CallIntMethod(env, JNI_result, getVal);
			if(val == tempJNI_result) {
				break;
			}
		}
		return JNI_result;

	}

	JNIEXPORT jobject JNICALL JNI_ktb_cipher_set_auth_data(JNIEnv *env, jclass cls, jlong ctx,jbyteArray auth_data) {

		jobject JNI_result;

		ktb_cipher_ctx_t C_ctx;
		if(ctx != 0) {
			C_ctx = (ktb_cipher_ctx_t)((contextWrapper *)ctx)->ctxRef;
			((contextWrapper *)ctx)->env = env;
		}
		else
			C_ctx = NULL;

		jbyte * C_auth_data;
		int C_auth_data_size = (*env)->GetArrayLength(env, auth_data);
		C_auth_data = (jbyte *)malloc(C_auth_data_size);
		C_auth_data = (*env)->GetByteArrayElements(env, auth_data, NULL);

		ktb_errno tempJNI_result = ktb_cipher_set_auth_data (C_ctx, C_auth_data, C_auth_data_size);

		(*env)->SetByteArrayRegion(env, auth_data, 0, C_auth_data_size, C_auth_data);
		int i_C_auth_data;
		for(i_C_auth_data = 0; i_C_auth_data < C_auth_data_size; ++i_C_auth_data)
			C_auth_data[i_C_auth_data] = 0;
		free(C_auth_data);

		jclass retObjCls = (*env)->FindClass(env, "ArcanaJNI$ktb_errno");
		jmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, "values", "()[LArcanaJNI$ktb_errno;");
		jobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);

		int arrayLength = (*env)->GetArrayLength(env, valuesArray);

		int i, val;
		jmethodID getVal;
		getVal = (*env)->GetMethodID(env, retObjCls, "getValue", "()I");

		for(i = 0; i < arrayLength; ++i)
		{
			JNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);
			val = (*env)->CallIntMethod(env, JNI_result, getVal);
			if(val == tempJNI_result) {
				break;
			}
		}
		return JNI_result;

	}

	JNIEXPORT jlong JNICALL JNI_ktb_cipher_get_prefix_size(JNIEnv *env, jclass cls, jlong ctx) {

		jlong JNI_result;

		ktb_cipher_ctx_t C_ctx;
		if(ctx != 0) {
			C_ctx = (ktb_cipher_ctx_t)((contextWrapper *)ctx)->ctxRef;
			((contextWrapper *)ctx)->env = env;
		}
		else
			C_ctx = NULL;

		 JNI_result = ktb_cipher_get_prefix_size (C_ctx);

		 return JNI_result;
	}

	JNIEXPORT jobject JNICALL JNI_ktb_cipher_get_prefix(JNIEnv *env, jclass cls, jlong ctx,jbyteArray prefix) {

		jobject JNI_result;

		ktb_cipher_ctx_t C_ctx;
		if(ctx != 0) {
			C_ctx = (ktb_cipher_ctx_t)((contextWrapper *)ctx)->ctxRef;
			((contextWrapper *)ctx)->env = env;
		}
		else
			C_ctx = NULL;

		jbyte * C_prefix;
		int C_prefix_size = (*env)->GetArrayLength(env, prefix);
		C_prefix = (jbyte *)malloc(C_prefix_size);
		C_prefix = (*env)->GetByteArrayElements(env, prefix, NULL);

		ktb_errno tempJNI_result = ktb_cipher_get_prefix (C_ctx, C_prefix, C_prefix_size);

		(*env)->SetByteArrayRegion(env, prefix, 0, C_prefix_size, C_prefix);
		int i_C_prefix;
		for(i_C_prefix = 0; i_C_prefix < C_prefix_size; ++i_C_prefix)
			C_prefix[i_C_prefix] = 0;
		free(C_prefix);

		jclass retObjCls = (*env)->FindClass(env, "ArcanaJNI$ktb_errno");
		jmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, "values", "()[LArcanaJNI$ktb_errno;");
		jobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);

		int arrayLength = (*env)->GetArrayLength(env, valuesArray);

		int i, val;
		jmethodID getVal;
		getVal = (*env)->GetMethodID(env, retObjCls, "getValue", "()I");

		for(i = 0; i < arrayLength; ++i)
		{
			JNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);
			val = (*env)->CallIntMethod(env, JNI_result, getVal);
			if(val == tempJNI_result) {
				break;
			}
		}
		return JNI_result;

	}

	JNIEXPORT jobject JNICALL JNI_ktb_cipher_set_prefix(JNIEnv *env, jclass cls, jlong ctx,jbyteArray prefix) {

		jobject JNI_result;

		ktb_cipher_ctx_t C_ctx;
		if(ctx != 0) {
			C_ctx = (ktb_cipher_ctx_t)((contextWrapper *)ctx)->ctxRef;
			((contextWrapper *)ctx)->env = env;
		}
		else
			C_ctx = NULL;

		jbyte * C_prefix;
		int C_prefix_size = (*env)->GetArrayLength(env, prefix);
		C_prefix = (jbyte *)malloc(C_prefix_size);
		C_prefix = (*env)->GetByteArrayElements(env, prefix, NULL);

		ktb_errno tempJNI_result = ktb_cipher_set_prefix (C_ctx, C_prefix, C_prefix_size);

		(*env)->SetByteArrayRegion(env, prefix, 0, C_prefix_size, C_prefix);
		int i_C_prefix;
		for(i_C_prefix = 0; i_C_prefix < C_prefix_size; ++i_C_prefix)
			C_prefix[i_C_prefix] = 0;
		free(C_prefix);

		jclass retObjCls = (*env)->FindClass(env, "ArcanaJNI$ktb_errno");
		jmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, "values", "()[LArcanaJNI$ktb_errno;");
		jobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);

		int arrayLength = (*env)->GetArrayLength(env, valuesArray);

		int i, val;
		jmethodID getVal;
		getVal = (*env)->GetMethodID(env, retObjCls, "getValue", "()I");

		for(i = 0; i < arrayLength; ++i)
		{
			JNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);
			val = (*env)->CallIntMethod(env, JNI_result, getVal);
			if(val == tempJNI_result) {
				break;
			}
		}
		return JNI_result;

	}

	JNIEXPORT jlong JNICALL JNI_ktb_cipher_get_suffix_size(JNIEnv *env, jclass cls, jlong ctx) {

		jlong JNI_result;

		ktb_cipher_ctx_t C_ctx;
		if(ctx != 0) {
			C_ctx = (ktb_cipher_ctx_t)((contextWrapper *)ctx)->ctxRef;
			((contextWrapper *)ctx)->env = env;
		}
		else
			C_ctx = NULL;

		 JNI_result = ktb_cipher_get_suffix_size (C_ctx);

		 return JNI_result;
	}

	JNIEXPORT jobject JNICALL JNI_ktb_cipher_get_suffix(JNIEnv *env, jclass cls, jlong ctx,jbyteArray suffix) {

		jobject JNI_result;

		ktb_cipher_ctx_t C_ctx;
		if(ctx != 0) {
			C_ctx = (ktb_cipher_ctx_t)((contextWrapper *)ctx)->ctxRef;
			((contextWrapper *)ctx)->env = env;
		}
		else
			C_ctx = NULL;

		jbyte * C_suffix;
		int C_suffix_size = (*env)->GetArrayLength(env, suffix);
		C_suffix = (jbyte *)malloc(C_suffix_size);
		C_suffix = (*env)->GetByteArrayElements(env, suffix, NULL);

		ktb_errno tempJNI_result = ktb_cipher_get_suffix (C_ctx, C_suffix, C_suffix_size);

		(*env)->SetByteArrayRegion(env, suffix, 0, C_suffix_size, C_suffix);
		int i_C_suffix;
		for(i_C_suffix = 0; i_C_suffix < C_suffix_size; ++i_C_suffix)
			C_suffix[i_C_suffix] = 0;
		free(C_suffix);

		jclass retObjCls = (*env)->FindClass(env, "ArcanaJNI$ktb_errno");
		jmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, "values", "()[LArcanaJNI$ktb_errno;");
		jobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);

		int arrayLength = (*env)->GetArrayLength(env, valuesArray);

		int i, val;
		jmethodID getVal;
		getVal = (*env)->GetMethodID(env, retObjCls, "getValue", "()I");

		for(i = 0; i < arrayLength; ++i)
		{
			JNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);
			val = (*env)->CallIntMethod(env, JNI_result, getVal);
			if(val == tempJNI_result) {
				break;
			}
		}
		return JNI_result;

	}

	JNIEXPORT jobject JNICALL JNI_ktb_cipher_encrypt_block(JNIEnv *env, jclass cls, jlong ctx,jbyteArray in,jbyteArray out) {

		jobject JNI_result;

		ktb_cipher_ctx_t C_ctx;
		if(ctx != 0) {
			C_ctx = (ktb_cipher_ctx_t)((contextWrapper *)ctx)->ctxRef;
			((contextWrapper *)ctx)->env = env;
		}
		else
			C_ctx = NULL;

		jbyte * C_in;
		int C_in_size = (*env)->GetArrayLength(env, in);
		C_in = (jbyte *)malloc(C_in_size);
		C_in = (*env)->GetByteArrayElements(env, in, NULL);

		jbyte * C_out;
		int C_out_size = (*env)->GetArrayLength(env, out);
		C_out = (jbyte *)malloc(C_out_size);
		C_out = (*env)->GetByteArrayElements(env, out, NULL);

		ktb_errno tempJNI_result = ktb_cipher_encrypt_block (C_ctx, C_in, C_in_size, C_out, C_out_size);

		(*env)->SetByteArrayRegion(env, in, 0, C_in_size, C_in);
		int i_C_in;
		for(i_C_in = 0; i_C_in < C_in_size; ++i_C_in)
			C_in[i_C_in] = 0;
		free(C_in);

		(*env)->SetByteArrayRegion(env, out, 0, C_out_size, C_out);
		int i_C_out;
		for(i_C_out = 0; i_C_out < C_out_size; ++i_C_out)
			C_out[i_C_out] = 0;
		free(C_out);

		jclass retObjCls = (*env)->FindClass(env, "ArcanaJNI$ktb_errno");
		jmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, "values", "()[LArcanaJNI$ktb_errno;");
		jobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);

		int arrayLength = (*env)->GetArrayLength(env, valuesArray);

		int i, val;
		jmethodID getVal;
		getVal = (*env)->GetMethodID(env, retObjCls, "getValue", "()I");

		for(i = 0; i < arrayLength; ++i)
		{
			JNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);
			val = (*env)->CallIntMethod(env, JNI_result, getVal);
			if(val == tempJNI_result) {
				break;
			}
		}
		return JNI_result;

	}

	JNIEXPORT jobject JNICALL JNI_ktb_cipher_decrypt_block(JNIEnv *env, jclass cls, jlong ctx,jbyteArray in,jbyteArray out) {

		jobject JNI_result;

		ktb_cipher_ctx_t C_ctx;
		if(ctx != 0) {
			C_ctx = (ktb_cipher_ctx_t)((contextWrapper *)ctx)->ctxRef;
			((contextWrapper *)ctx)->env = env;
		}
		else
			C_ctx = NULL;

		jbyte * C_in;
		int C_in_size = (*env)->GetArrayLength(env, in);
		C_in = (jbyte *)malloc(C_in_size);
		C_in = (*env)->GetByteArrayElements(env, in, NULL);

		jbyte * C_out;
		int C_out_size = (*env)->GetArrayLength(env, out);
		C_out = (jbyte *)malloc(C_out_size);
		C_out = (*env)->GetByteArrayElements(env, out, NULL);

		ktb_errno tempJNI_result = ktb_cipher_decrypt_block (C_ctx, C_in, C_in_size, C_out, C_out_size);

		(*env)->SetByteArrayRegion(env, in, 0, C_in_size, C_in);
		int i_C_in;
		for(i_C_in = 0; i_C_in < C_in_size; ++i_C_in)
			C_in[i_C_in] = 0;
		free(C_in);

		(*env)->SetByteArrayRegion(env, out, 0, C_out_size, C_out);
		int i_C_out;
		for(i_C_out = 0; i_C_out < C_out_size; ++i_C_out)
			C_out[i_C_out] = 0;
		free(C_out);

		jclass retObjCls = (*env)->FindClass(env, "ArcanaJNI$ktb_errno");
		jmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, "values", "()[LArcanaJNI$ktb_errno;");
		jobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);

		int arrayLength = (*env)->GetArrayLength(env, valuesArray);

		int i, val;
		jmethodID getVal;
		getVal = (*env)->GetMethodID(env, retObjCls, "getValue", "()I");

		for(i = 0; i < arrayLength; ++i)
		{
			JNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);
			val = (*env)->CallIntMethod(env, JNI_result, getVal);
			if(val == tempJNI_result) {
				break;
			}
		}
		return JNI_result;

	}

	JNIEXPORT void JNICALL JNI_ktb_cipher_finalise(JNIEnv *env, jclass cls, jlong ctx) {

		ktb_cipher_ctx_t C_ctx;
		if(ctx != 0) {
			C_ctx = (ktb_cipher_ctx_t)((contextWrapper *)ctx)->ctxRef;
			((contextWrapper *)ctx)->env = env;
		}
		else
			C_ctx = NULL;

		  ktb_cipher_finalise (C_ctx);

	}

	JNIEXPORT jbyteArray JNICALL JNI_ktb_cipher_get_mac(JNIEnv *env, jclass cls, jlong ctx) {

		jbyteArray JNI_result;

		ktb_cipher_ctx_t C_ctx;
		if(ctx != 0) {
			C_ctx = (ktb_cipher_ctx_t)((contextWrapper *)ctx)->ctxRef;
			((contextWrapper *)ctx)->env = env;
		}
		else
			C_ctx = NULL;

		size_t C_size;

		void* tempJNI_result = (void*)ktb_cipher_get_mac (C_ctx, &C_size);

		JNI_result = (*env)->NewByteArray(env, C_size);
		(*env)->SetByteArrayRegion(env, JNI_result, 0, C_size, (jbyte *)tempJNI_result);
		return JNI_result;
	}

	JNIEXPORT jlong JNICALL JNI_ktb_cipher_get_data_size(JNIEnv *env, jclass cls, jlong ctx) {

		jlong JNI_result;

		ktb_cipher_ctx_t C_ctx;
		if(ctx != 0) {
			C_ctx = (ktb_cipher_ctx_t)((contextWrapper *)ctx)->ctxRef;
			((contextWrapper *)ctx)->env = env;
		}
		else
			C_ctx = NULL;

		 JNI_result = ktb_cipher_get_data_size (C_ctx);

		 return JNI_result;
	}

	JNIEXPORT jstring JNICALL JNI_ktb_cipher_get_name_from_algo(JNIEnv *env, jclass cls, jobject algo) {

		jstring JNI_result;

		jclass enm_algo;
		enm_algo = (*env)->GetObjectClass(env, algo);
		jmethodID get_algo = (*env)->GetMethodID(env, enm_algo, "getValue", "()I");
		jint algo_value = (*env)->CallIntMethod(env, algo, get_algo);
		ktb_cipher_algo_t C_algo = (ktb_cipher_algo_t)algo_value;

		char * tempJNI_result = (char *)ktb_cipher_get_name_from_algo (C_algo);

		JNI_result = (*env)->NewStringUTF(env, tempJNI_result);
		 return JNI_result;
	}

	JNIEXPORT jstring JNICALL JNI_ktb_cipher_get_name_from_mode(JNIEnv *env, jclass cls, jobject mode) {

		jstring JNI_result;

		jclass enm_mode;
		enm_mode = (*env)->GetObjectClass(env, mode);
		jmethodID get_mode = (*env)->GetMethodID(env, enm_mode, "getValue", "()I");
		jint mode_value = (*env)->CallIntMethod(env, mode, get_mode);
		ktb_cipher_mode_t C_mode = (ktb_cipher_mode_t)mode_value;

		char * tempJNI_result = (char *)ktb_cipher_get_name_from_mode (C_mode);

		JNI_result = (*env)->NewStringUTF(env, tempJNI_result);
		 return JNI_result;
	}

	JNIEXPORT jlong JNICALL JNI_ktb_cipher_get_key_len(JNIEnv *env, jclass cls, jlong ctx) {

		jlong JNI_result;

		ktb_cipher_ctx_t C_ctx;
		if(ctx != 0) {
			C_ctx = (ktb_cipher_ctx_t)((contextWrapper *)ctx)->ctxRef;
			((contextWrapper *)ctx)->env = env;
		}
		else
			C_ctx = NULL;

		 JNI_result = ktb_cipher_get_key_len (C_ctx);

		 return JNI_result;
	}

	JNIEXPORT jlong JNICALL JNI_ktb_cipher_get_block_len(JNIEnv *env, jclass cls, jlong ctx) {

		jlong JNI_result;

		ktb_cipher_ctx_t C_ctx;
		if(ctx != 0) {
			C_ctx = (ktb_cipher_ctx_t)((contextWrapper *)ctx)->ctxRef;
			((contextWrapper *)ctx)->env = env;
		}
		else
			C_ctx = NULL;

		 JNI_result = ktb_cipher_get_block_len (C_ctx);

		 return JNI_result;
	}

	JNIEXPORT jlong JNICALL JNI_ktb_cipher_get_iv_len(JNIEnv *env, jclass cls, jlong ctx) {

		jlong JNI_result;

		ktb_cipher_ctx_t C_ctx;
		if(ctx != 0) {
			C_ctx = (ktb_cipher_ctx_t)((contextWrapper *)ctx)->ctxRef;
			((contextWrapper *)ctx)->env = env;
		}
		else
			C_ctx = NULL;

		 JNI_result = ktb_cipher_get_iv_len (C_ctx);

		 return JNI_result;
	}

	JNIEXPORT jlong JNICALL JNI_ktb_cipher_get_mac_size(JNIEnv *env, jclass cls, jlong ctx) {

		jlong JNI_result;

		ktb_cipher_ctx_t C_ctx;
		if(ctx != 0) {
			C_ctx = (ktb_cipher_ctx_t)((contextWrapper *)ctx)->ctxRef;
			((contextWrapper *)ctx)->env = env;
		}
		else
			C_ctx = NULL;

		 JNI_result = ktb_cipher_get_mac_size (C_ctx);

		 return JNI_result;
	}

	JNIEXPORT jlong JNICALL JNI_ktb_cipher_get_iv_len_from_mode(JNIEnv *env, jclass cls, jobject mode) {

		jlong JNI_result;

		jclass enm_mode;
		enm_mode = (*env)->GetObjectClass(env, mode);
		jmethodID get_mode = (*env)->GetMethodID(env, enm_mode, "getValue", "()I");
		jint mode_value = (*env)->CallIntMethod(env, mode, get_mode);
		ktb_cipher_mode_t C_mode = (ktb_cipher_mode_t)mode_value;

		 JNI_result = ktb_cipher_get_iv_len_from_mode (C_mode);

		 return JNI_result;
	}

	JNIEXPORT jobject JNICALL JNI_ktb_hash_init(JNIEnv *env, jclass cls, jobject ctx,jobject algo) {

		jobject JNI_result;

		ktb_hash_ctx_t C_ctx;
		contextWrapper *ctxWrp1 = (contextWrapper *)malloc(sizeof(contextWrapper));
		ctxWrp1->env = env;

		jclass enm_algo;
		enm_algo = (*env)->GetObjectClass(env, algo);
		jmethodID get_algo = (*env)->GetMethodID(env, enm_algo, "getValue", "()I");
		jint algo_value = (*env)->CallIntMethod(env, algo, get_algo);
		ktb_hash_algo_t C_algo = (ktb_hash_algo_t)algo_value;

		ktb_errno tempJNI_result = ktb_hash_init (&C_ctx, C_algo);

		ctxWrp1->ctxRef = C_ctx;
		jclass adrWrp_ctx;
		jmethodID setAddr_ctx;
		jlong arg_ctx;

		adrWrp_ctx = (*env)->GetObjectClass(env, ctx);
		setAddr_ctx = (*env)->GetMethodID(env, adrWrp_ctx, "setAddress", "(J)V");
		arg_ctx = (jlong) ctxWrp1;
		(*env)->CallVoidMethod(env, ctx, setAddr_ctx, arg_ctx);

		jclass retObjCls = (*env)->FindClass(env, "ArcanaJNI$ktb_errno");
		jmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, "values", "()[LArcanaJNI$ktb_errno;");
		jobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);

		int arrayLength = (*env)->GetArrayLength(env, valuesArray);

		int i, val;
		jmethodID getVal;
		getVal = (*env)->GetMethodID(env, retObjCls, "getValue", "()I");

		for(i = 0; i < arrayLength; ++i)
		{
			JNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);
			val = (*env)->CallIntMethod(env, JNI_result, getVal);
			if(val == tempJNI_result) {
				break;
			}
		}
		return JNI_result;

	}

	JNIEXPORT jobject JNICALL JNI_ktb_hash_init_hmac(JNIEnv *env, jclass cls, jobject ctx,jobject algo,jbyteArray key) {

		jobject JNI_result;

		ktb_hash_ctx_t C_ctx;
		contextWrapper *ctxWrp2 = (contextWrapper *)malloc(sizeof(contextWrapper));
		ctxWrp2->env = env;

		jclass enm_algo;
		enm_algo = (*env)->GetObjectClass(env, algo);
		jmethodID get_algo = (*env)->GetMethodID(env, enm_algo, "getValue", "()I");
		jint algo_value = (*env)->CallIntMethod(env, algo, get_algo);
		ktb_hash_algo_t C_algo = (ktb_hash_algo_t)algo_value;

		jbyte * C_key;
		int C_key_size = (*env)->GetArrayLength(env, key);
		C_key = (jbyte *)malloc(C_key_size);
		C_key = (*env)->GetByteArrayElements(env, key, NULL);

		ktb_errno tempJNI_result = ktb_hash_init_hmac (&C_ctx, C_algo, C_key, C_key_size);

		ctxWrp2->ctxRef = C_ctx;
		jclass adrWrp_ctx;
		jmethodID setAddr_ctx;
		jlong arg_ctx;

		adrWrp_ctx = (*env)->GetObjectClass(env, ctx);
		setAddr_ctx = (*env)->GetMethodID(env, adrWrp_ctx, "setAddress", "(J)V");
		arg_ctx = (jlong) ctxWrp2;
		(*env)->CallVoidMethod(env, ctx, setAddr_ctx, arg_ctx);

		(*env)->SetByteArrayRegion(env, key, 0, C_key_size, C_key);
		int i_C_key;
		for(i_C_key = 0; i_C_key < C_key_size; ++i_C_key)
			C_key[i_C_key] = 0;
		free(C_key);

		jclass retObjCls = (*env)->FindClass(env, "ArcanaJNI$ktb_errno");
		jmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, "values", "()[LArcanaJNI$ktb_errno;");
		jobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);

		int arrayLength = (*env)->GetArrayLength(env, valuesArray);

		int i, val;
		jmethodID getVal;
		getVal = (*env)->GetMethodID(env, retObjCls, "getValue", "()I");

		for(i = 0; i < arrayLength; ++i)
		{
			JNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);
			val = (*env)->CallIntMethod(env, JNI_result, getVal);
			if(val == tempJNI_result) {
				break;
			}
		}
		return JNI_result;

	}

	JNIEXPORT void JNICALL JNI_ktb_hash_clear(JNIEnv *env, jclass cls, jlong ctx) {

		ktb_hash_ctx_t C_ctx;
		if(ctx != 0) {
			C_ctx = (ktb_hash_ctx_t)((contextWrapper *)ctx)->ctxRef;
			((contextWrapper *)ctx)->env = env;
		}
		else
			C_ctx = NULL;

		  ktb_hash_clear (C_ctx);

	}

	JNIEXPORT void JNICALL JNI_ktb_hash_reset(JNIEnv *env, jclass cls, jlong ctx) {

		ktb_hash_ctx_t C_ctx;
		if(ctx != 0) {
			C_ctx = (ktb_hash_ctx_t)((contextWrapper *)ctx)->ctxRef;
			((contextWrapper *)ctx)->env = env;
		}
		else
			C_ctx = NULL;

		  ktb_hash_reset (C_ctx);

	}

	JNIEXPORT void JNICALL JNI_ktb_hash_process(JNIEnv *env, jclass cls, jlong ctx,jbyteArray buf) {

		ktb_hash_ctx_t C_ctx;
		if(ctx != 0) {
			C_ctx = (ktb_hash_ctx_t)((contextWrapper *)ctx)->ctxRef;
			((contextWrapper *)ctx)->env = env;
		}
		else
			C_ctx = NULL;

		jbyte * C_buf;
		int C_buf_size = (*env)->GetArrayLength(env, buf);
		C_buf = (jbyte *)malloc(C_buf_size);
		C_buf = (*env)->GetByteArrayElements(env, buf, NULL);

		  ktb_hash_process (C_ctx, C_buf, C_buf_size);

		(*env)->SetByteArrayRegion(env, buf, 0, C_buf_size, C_buf);
		int i_C_buf;
		for(i_C_buf = 0; i_C_buf < C_buf_size; ++i_C_buf)
			C_buf[i_C_buf] = 0;
		free(C_buf);

	}

	JNIEXPORT void JNICALL JNI_ktb_hash_finalise(JNIEnv *env, jclass cls, jlong ctx) {

		ktb_hash_ctx_t C_ctx;
		if(ctx != 0) {
			C_ctx = (ktb_hash_ctx_t)((contextWrapper *)ctx)->ctxRef;
			((contextWrapper *)ctx)->env = env;
		}
		else
			C_ctx = NULL;

		  ktb_hash_finalise (C_ctx);

	}

	JNIEXPORT jbyteArray JNICALL JNI_ktb_hash_retrieve(JNIEnv *env, jclass cls, jlong ctx) {

		jbyteArray JNI_result;

		ktb_hash_ctx_t C_ctx;
		if(ctx != 0) {
			C_ctx = (ktb_hash_ctx_t)((contextWrapper *)ctx)->ctxRef;
			((contextWrapper *)ctx)->env = env;
		}
		else
			C_ctx = NULL;

		size_t C_size;

		void* tempJNI_result = (void*)ktb_hash_retrieve (C_ctx, &C_size);

		JNI_result = (*env)->NewByteArray(env, C_size);
		(*env)->SetByteArrayRegion(env, JNI_result, 0, C_size, (jbyte *)tempJNI_result);
		return JNI_result;
	}

	JNIEXPORT jstring JNICALL JNI_ktb_hash_get_name(JNIEnv *env, jclass cls, jlong ctx) {

		jstring JNI_result;

		ktb_hash_ctx_t C_ctx;
		if(ctx != 0) {
			C_ctx = (ktb_hash_ctx_t)((contextWrapper *)ctx)->ctxRef;
			((contextWrapper *)ctx)->env = env;
		}
		else
			C_ctx = NULL;

		char * tempJNI_result = (char *)ktb_hash_get_name (C_ctx);

		JNI_result = (*env)->NewStringUTF(env, tempJNI_result);
		 return JNI_result;
	}

	JNIEXPORT jstring JNICALL JNI_ktb_hash_get_name_from_algo(JNIEnv *env, jclass cls, jobject algo) {

		jstring JNI_result;

		jclass enm_algo;
		enm_algo = (*env)->GetObjectClass(env, algo);
		jmethodID get_algo = (*env)->GetMethodID(env, enm_algo, "getValue", "()I");
		jint algo_value = (*env)->CallIntMethod(env, algo, get_algo);
		ktb_hash_algo_t C_algo = (ktb_hash_algo_t)algo_value;

		char * tempJNI_result = (char *)ktb_hash_get_name_from_algo (C_algo);

		JNI_result = (*env)->NewStringUTF(env, tempJNI_result);
		 return JNI_result;
	}

	JNIEXPORT jlong JNICALL JNI_ktb_hash_get_len(JNIEnv *env, jclass cls, jlong ctx) {

		jlong JNI_result;

		ktb_hash_ctx_t C_ctx;
		if(ctx != 0) {
			C_ctx = (ktb_hash_ctx_t)((contextWrapper *)ctx)->ctxRef;
			((contextWrapper *)ctx)->env = env;
		}
		else
			C_ctx = NULL;

		 JNI_result = ktb_hash_get_len (C_ctx);

		 return JNI_result;
	}

	JNIEXPORT jlong JNICALL JNI_ktb_hash_get_len_from_algo(JNIEnv *env, jclass cls, jobject algo) {

		jlong JNI_result;

		jclass enm_algo;
		enm_algo = (*env)->GetObjectClass(env, algo);
		jmethodID get_algo = (*env)->GetMethodID(env, enm_algo, "getValue", "()I");
		jint algo_value = (*env)->CallIntMethod(env, algo, get_algo);
		ktb_hash_algo_t C_algo = (ktb_hash_algo_t)algo_value;

		 JNI_result = ktb_hash_get_len_from_algo (C_algo);

		 return JNI_result;
	}

	JNIEXPORT jlong JNICALL JNI_ktb_hash_get_block_size(JNIEnv *env, jclass cls, jlong ctx) {

		jlong JNI_result;

		ktb_hash_ctx_t C_ctx;
		if(ctx != 0) {
			C_ctx = (ktb_hash_ctx_t)((contextWrapper *)ctx)->ctxRef;
			((contextWrapper *)ctx)->env = env;
		}
		else
			C_ctx = NULL;

		 JNI_result = ktb_hash_get_block_size (C_ctx);

		 return JNI_result;
	}

	JNIEXPORT jobject JNICALL JNI_ktb_hash_block(JNIEnv *env, jclass cls, jobject algo,jbyteArray block,jbyteArray result) {

		jobject JNI_result;

		jclass enm_algo;
		enm_algo = (*env)->GetObjectClass(env, algo);
		jmethodID get_algo = (*env)->GetMethodID(env, enm_algo, "getValue", "()I");
		jint algo_value = (*env)->CallIntMethod(env, algo, get_algo);
		ktb_hash_algo_t C_algo = (ktb_hash_algo_t)algo_value;

		jbyte * C_block;
		int C_block_size = (*env)->GetArrayLength(env, block);
		C_block = (jbyte *)malloc(C_block_size);
		C_block = (*env)->GetByteArrayElements(env, block, NULL);

		jbyte * C_result;
		int C_result_size = (*env)->GetArrayLength(env, result);
		C_result = (jbyte *)malloc(C_result_size);
		C_result = (*env)->GetByteArrayElements(env, result, NULL);

		ktb_errno tempJNI_result = ktb_hash_block (C_algo, C_block, C_block_size, C_result, C_result_size);

		(*env)->SetByteArrayRegion(env, block, 0, C_block_size, C_block);
		int i_C_block;
		for(i_C_block = 0; i_C_block < C_block_size; ++i_C_block)
			C_block[i_C_block] = 0;
		free(C_block);

		(*env)->SetByteArrayRegion(env, result, 0, C_result_size, C_result);
		int i_C_result;
		for(i_C_result = 0; i_C_result < C_result_size; ++i_C_result)
			C_result[i_C_result] = 0;
		free(C_result);

		jclass retObjCls = (*env)->FindClass(env, "ArcanaJNI$ktb_errno");
		jmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, "values", "()[LArcanaJNI$ktb_errno;");
		jobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);

		int arrayLength = (*env)->GetArrayLength(env, valuesArray);

		int i, val;
		jmethodID getVal;
		getVal = (*env)->GetMethodID(env, retObjCls, "getValue", "()I");

		for(i = 0; i < arrayLength; ++i)
		{
			JNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);
			val = (*env)->CallIntMethod(env, JNI_result, getVal);
			if(val == tempJNI_result) {
				break;
			}
		}
		return JNI_result;

	}

	JNIEXPORT jint JNICALL JNI_ktb_curves_count(JNIEnv *env, jclass cls) {

		jint JNI_result;

		 JNI_result = ktb_curves_count ();

		 return JNI_result;
	}

	JNIEXPORT jstring JNICALL JNI_ktb_curves_id(JNIEnv *env, jclass cls, jint index) {

		jstring JNI_result;

		int C_index = (int) index;

		char * tempJNI_result = (char *)ktb_curves_id (C_index);

		JNI_result = (*env)->NewStringUTF(env, tempJNI_result);
		 return JNI_result;
	}

	JNIEXPORT jlong JNICALL JNI_ktb_base64_encode_size(JNIEnv *env, jclass cls, jlong input_size) {

		jlong JNI_result;

		size_t C_input_size = (size_t) input_size;

		 JNI_result = ktb_base64_encode_size (C_input_size);

		 return JNI_result;
	}

	JNIEXPORT jobject JNICALL JNI_ktb_base64_encode(JNIEnv *env, jclass cls, jbyteArray input,jbyteArray result) {

		jobject JNI_result;

		jbyte * C_input;
		int C_input_size = (*env)->GetArrayLength(env, input);
		C_input = (jbyte *)malloc(C_input_size);
		C_input = (*env)->GetByteArrayElements(env, input, NULL);

		jbyte * C_result;
		int C_result_size = (*env)->GetArrayLength(env, result);
		C_result = (jbyte *)malloc(C_result_size);
		C_result = (*env)->GetByteArrayElements(env, result, NULL);

		ktb_errno tempJNI_result = ktb_base64_encode (C_input, C_input_size, C_result, C_result_size);

		(*env)->SetByteArrayRegion(env, input, 0, C_input_size, C_input);
		int i_C_input;
		for(i_C_input = 0; i_C_input < C_input_size; ++i_C_input)
			C_input[i_C_input] = 0;
		free(C_input);

		(*env)->SetByteArrayRegion(env, result, 0, C_result_size, C_result);
		int i_C_result;
		for(i_C_result = 0; i_C_result < C_result_size; ++i_C_result)
			C_result[i_C_result] = 0;
		free(C_result);

		jclass retObjCls = (*env)->FindClass(env, "ArcanaJNI$ktb_errno");
		jmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, "values", "()[LArcanaJNI$ktb_errno;");
		jobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);

		int arrayLength = (*env)->GetArrayLength(env, valuesArray);

		int i, val;
		jmethodID getVal;
		getVal = (*env)->GetMethodID(env, retObjCls, "getValue", "()I");

		for(i = 0; i < arrayLength; ++i)
		{
			JNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);
			val = (*env)->CallIntMethod(env, JNI_result, getVal);
			if(val == tempJNI_result) {
				break;
			}
		}
		return JNI_result;

	}

	JNIEXPORT jlong JNICALL JNI_ktb_base64_decode_size(JNIEnv *env, jclass cls, jbyteArray input) {

		jlong JNI_result;

		jbyte * C_input;
		int C_input_size = (*env)->GetArrayLength(env, input);
		C_input = (jbyte *)malloc(C_input_size);
		C_input = (*env)->GetByteArrayElements(env, input, NULL);

		 JNI_result = ktb_base64_decode_size (C_input, C_input_size);

		(*env)->SetByteArrayRegion(env, input, 0, C_input_size, C_input);
		int i_C_input;
		for(i_C_input = 0; i_C_input < C_input_size; ++i_C_input)
			C_input[i_C_input] = 0;
		free(C_input);

		 return JNI_result;
	}

	JNIEXPORT jobject JNICALL JNI_ktb_base64_decode(JNIEnv *env, jclass cls, jbyteArray input,jbyteArray result) {

		jobject JNI_result;

		jbyte * C_input;
		int C_input_size = (*env)->GetArrayLength(env, input);
		C_input = (jbyte *)malloc(C_input_size);
		C_input = (*env)->GetByteArrayElements(env, input, NULL);

		jbyte * C_result;
		int C_result_size = (*env)->GetArrayLength(env, result);
		C_result = (jbyte *)malloc(C_result_size);
		C_result = (*env)->GetByteArrayElements(env, result, NULL);

		ktb_errno tempJNI_result = ktb_base64_decode (C_input, C_input_size, C_result, C_result_size);

		(*env)->SetByteArrayRegion(env, input, 0, C_input_size, C_input);
		int i_C_input;
		for(i_C_input = 0; i_C_input < C_input_size; ++i_C_input)
			C_input[i_C_input] = 0;
		free(C_input);

		(*env)->SetByteArrayRegion(env, result, 0, C_result_size, C_result);
		int i_C_result;
		for(i_C_result = 0; i_C_result < C_result_size; ++i_C_result)
			C_result[i_C_result] = 0;
		free(C_result);

		jclass retObjCls = (*env)->FindClass(env, "ArcanaJNI$ktb_errno");
		jmethodID getArrayValues = (*env)->GetStaticMethodID(env, retObjCls, "values", "()[LArcanaJNI$ktb_errno;");
		jobjectArray valuesArray = (jobjectArray)(*env)->CallStaticObjectMethod(env, retObjCls, getArrayValues);

		int arrayLength = (*env)->GetArrayLength(env, valuesArray);

		int i, val;
		jmethodID getVal;
		getVal = (*env)->GetMethodID(env, retObjCls, "getValue", "()I");

		for(i = 0; i < arrayLength; ++i)
		{
			JNI_result = (*env)->GetObjectArrayElement(env, valuesArray, i);
			val = (*env)->CallIntMethod(env, JNI_result, getVal);
			if(val == tempJNI_result) {
				break;
			}
		}
		return JNI_result;

	}

static JNINativeMethod method_table[] = {
	{ "gen_jni_ktb_kep_dh_t_create", "()J", (void *)JNI_gen_jni_ktb_kep_dh_t_create },
	{ "gen_jni_ktb_kep_dh_t_free", "(J)V", (void *)JNI_gen_jni_ktb_kep_dh_t_free },
	{ "gen_jni_ktb_kep_dh_t_get_struct_size", "()J", (void *)JNI_gen_jni_ktb_kep_dh_t_get_struct_size },
	{ "gen_jni_ktb_kep_dh_t_get_dummy", "(J)I", (void *)JNI_gen_jni_ktb_kep_dh_t_get_dummy },
	{ "gen_jni_ktb_kep_dh_t_set_dummy", "(JI)V", (void *)JNI_gen_jni_ktb_kep_dh_t_set_dummy },
	{ "gen_jni_ktb_kep_dh_pass_t_create", "()J", (void *)JNI_gen_jni_ktb_kep_dh_pass_t_create },
	{ "gen_jni_ktb_kep_dh_pass_t_free", "(J)V", (void *)JNI_gen_jni_ktb_kep_dh_pass_t_free },
	{ "gen_jni_ktb_kep_dh_pass_t_get_struct_size", "()J", (void *)JNI_gen_jni_ktb_kep_dh_pass_t_get_struct_size },
	{ "gen_jni_ktb_kep_dh_pass_t_get_cipher_algo", "(J)LArcanaJNI$ktb_cipher_algo_t;", (void *)JNI_gen_jni_ktb_kep_dh_pass_t_get_cipher_algo },
	{ "gen_jni_ktb_kep_dh_pass_t_get_discuss_key", "(J)[B", (void *)JNI_gen_jni_ktb_kep_dh_pass_t_get_discuss_key },
	{ "gen_jni_ktb_kep_dh_pass_t_get_discuss_key_size", "(J)J", (void *)JNI_gen_jni_ktb_kep_dh_pass_t_get_discuss_key_size },
	{ "gen_jni_ktb_kep_dh_pass_t_set_cipher_algo", "(JLArcanaJNI$ktb_cipher_algo_t;)V", (void *)JNI_gen_jni_ktb_kep_dh_pass_t_set_cipher_algo },
	{ "gen_jni_ktb_kep_dh_pass_t_set_discuss_key", "(J[B)V", (void *)JNI_gen_jni_ktb_kep_dh_pass_t_set_discuss_key },
	{ "gen_jni_ktb_kep_dh_pass_t_set_discuss_key_size", "(JJ)V", (void *)JNI_gen_jni_ktb_kep_dh_pass_t_set_discuss_key_size },
	{ "gen_jni_ktb_kep_sts_t_create", "()J", (void *)JNI_gen_jni_ktb_kep_sts_t_create },
	{ "gen_jni_ktb_kep_sts_t_free", "(J)V", (void *)JNI_gen_jni_ktb_kep_sts_t_free },
	{ "gen_jni_ktb_kep_sts_t_get_struct_size", "()J", (void *)JNI_gen_jni_ktb_kep_sts_t_get_struct_size },
	{ "gen_jni_ktb_kep_sts_t_get_cipher_algo", "(J)LArcanaJNI$ktb_cipher_algo_t;", (void *)JNI_gen_jni_ktb_kep_sts_t_get_cipher_algo },
	{ "gen_jni_ktb_kep_sts_t_get_peer_public_key", "(J)J", (void *)JNI_gen_jni_ktb_kep_sts_t_get_peer_public_key },
	{ "gen_jni_ktb_kep_sts_t_get_self_private_key", "(J)J", (void *)JNI_gen_jni_ktb_kep_sts_t_get_self_private_key },
	{ "gen_jni_ktb_kep_sts_t_set_cipher_algo", "(JLArcanaJNI$ktb_cipher_algo_t;)V", (void *)JNI_gen_jni_ktb_kep_sts_t_set_cipher_algo },
	{ "gen_jni_ktb_kep_sts_t_set_peer_public_key", "(JJ)V", (void *)JNI_gen_jni_ktb_kep_sts_t_set_peer_public_key },
	{ "gen_jni_ktb_kep_sts_t_set_self_private_key", "(JJ)V", (void *)JNI_gen_jni_ktb_kep_sts_t_set_self_private_key },
	{ "ktb_kep_init", "(LArcanaJNI$AddressWrapper;JLArcanaJNI$ktb_kep_algo_t;JJLjava/lang/String;LArcanaJNI$ktb_hash_algo_t;JI)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_kep_init },
	{ "ktb_kep_clear", "(J)V", (void *)JNI_ktb_kep_clear },
	{ "ktb_kep_get_data", "(J)[B", (void *)JNI_ktb_kep_get_data },
	{ "ktb_kep_put_data", "(J[BLArcanaJNI$BoolWrapper;)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_kep_put_data },
	{ "ktb_kep_finalise", "(J[B)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_kep_finalise },
	{ "ktb_kep_get_algo_name", "(LArcanaJNI$ktb_kep_algo_t;)Ljava/lang/String;", (void *)JNI_ktb_kep_get_algo_name },
	{ "ktb_init", "()LArcanaJNI$ktb_errno;", (void *)JNI_ktb_init },
	{ "ktb_clear", "()V", (void *)JNI_ktb_clear },
	{ "ktb_sign_init", "(LArcanaJNI$AddressWrapper;LArcanaJNI$ktb_hash_algo_t;)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_sign_init },
	{ "ktb_sign_clear", "(J)V", (void *)JNI_ktb_sign_clear },
	{ "ktb_sign_reset", "(J)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_sign_reset },
	{ "ktb_sign_process", "(J[B)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_sign_process },
	{ "ktb_sign_finalise", "(J)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_sign_finalise },
	{ "ktb_sign_set_public_key", "(JJ)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_sign_set_public_key },
	{ "ktb_sign_verify", "(J[BLArcanaJNI$BoolWrapper;)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_sign_verify },
	{ "ktb_sign_verify_block", "(LArcanaJNI$ktb_hash_algo_t;J[B[BLArcanaJNI$BoolWrapper;)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_sign_verify_block },
	{ "ktb_sign_set_private_key", "(JJJ)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_sign_set_private_key },
	{ "ktb_sign_get_sign_size", "(J)J", (void *)JNI_ktb_sign_get_sign_size },
	{ "ktb_sign_get_sign", "(J)[B", (void *)JNI_ktb_sign_get_sign },
	{ "ktb_sign_get_sign_size_from_key", "(J)J", (void *)JNI_ktb_sign_get_sign_size_from_key },
	{ "ktb_sign_sign_block", "(LArcanaJNI$ktb_hash_algo_t;JJ[B[B)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_sign_sign_block },
	{ "ktb_kdf", "(LArcanaJNI$ktb_hash_algo_t;[B[B)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_kdf },
	{ "ktb_pbkdf", "(LArcanaJNI$ktb_hash_algo_t;[B[BJ[B)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_pbkdf },
	{ "ktb_kdf_max_size", "(LArcanaJNI$ktb_hash_algo_t;)J", (void *)JNI_ktb_kdf_max_size },
	{ "ktb_strerror", "(LArcanaJNI$ktb_errno;[B)I", (void *)JNI_ktb_strerror },
	{ "ktb_kem_psec_encrypt_size", "(J)J", (void *)JNI_ktb_kem_psec_encrypt_size },
	{ "ktb_kem_psec_encrypt", "(LArcanaJNI$ktb_hash_algo_t;JJ[B[B)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_kem_psec_encrypt },
	{ "ktb_kem_psec_decrypt", "(LArcanaJNI$ktb_hash_algo_t;J[B[B)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_kem_psec_decrypt },
	{ "ktb_prng_clear", "(J)V", (void *)JNI_ktb_prng_clear },
	{ "ktb_prng_reseed_with", "(J[B)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_prng_reseed_with },
	{ "ktb_prng_reseed", "(J)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_prng_reseed },
	{ "ktb_prng_fill_buffer", "(J[B)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_prng_fill_buffer },
	{ "ktb_keys_public_key_clear", "(J)V", (void *)JNI_ktb_keys_public_key_clear },
	{ "ktb_keys_private_key_clear", "(J)V", (void *)JNI_ktb_keys_private_key_clear },
	{ "ktb_keys_public_key_export_size", "(J)J", (void *)JNI_ktb_keys_public_key_export_size },
	{ "ktb_keys_public_key_export", "(J[B)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_keys_public_key_export },
	{ "ktb_keys_public_key_import", "([BLArcanaJNI$AddressWrapper;)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_keys_public_key_import },
	{ "ktb_keys_private_key_export_size", "(J)J", (void *)JNI_ktb_keys_private_key_export_size },
	{ "ktb_keys_private_key_export", "(J[B)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_keys_private_key_export },
	{ "ktb_keys_private_key_import", "([BLArcanaJNI$AddressWrapper;)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_keys_private_key_import },
	{ "ktb_keys_generate_keypair", "(JLjava/lang/String;LArcanaJNI$AddressWrapper;LArcanaJNI$AddressWrapper;)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_keys_generate_keypair },
	{ "ktb_radix64_encode_size", "(J)J", (void *)JNI_ktb_radix64_encode_size },
	{ "ktb_radix64_encode", "([B[B)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_radix64_encode },
	{ "ktb_radix64_decode_size", "([B)J", (void *)JNI_ktb_radix64_decode_size },
	{ "ktb_radix64_decode", "([B[B)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_radix64_decode },
	{ "ktb_radix64_verify", "([BLArcanaJNI$BoolWrapper;)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_radix64_verify },
	{ "ktb_cipher_init", "(LArcanaJNI$AddressWrapper;LArcanaJNI$ktb_cipher_algo_t;LArcanaJNI$ktb_cipher_mode_t;Z)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_cipher_init },
	{ "ktb_cipher_clear", "(J)V", (void *)JNI_ktb_cipher_clear },
	{ "ktb_cipher_reset", "(J)V", (void *)JNI_ktb_cipher_reset },
	{ "ktb_cipher_set_key", "(J[B)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_cipher_set_key },
	{ "ktb_cipher_set_iv", "(J[B)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_cipher_set_iv },
	{ "ktb_cipher_set_auth_data", "(J[B)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_cipher_set_auth_data },
	{ "ktb_cipher_get_prefix_size", "(J)J", (void *)JNI_ktb_cipher_get_prefix_size },
	{ "ktb_cipher_get_prefix", "(J[B)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_cipher_get_prefix },
	{ "ktb_cipher_set_prefix", "(J[B)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_cipher_set_prefix },
	{ "ktb_cipher_get_suffix_size", "(J)J", (void *)JNI_ktb_cipher_get_suffix_size },
	{ "ktb_cipher_get_suffix", "(J[B)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_cipher_get_suffix },
	{ "ktb_cipher_encrypt_block", "(J[B[B)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_cipher_encrypt_block },
	{ "ktb_cipher_decrypt_block", "(J[B[B)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_cipher_decrypt_block },
	{ "ktb_cipher_finalise", "(J)V", (void *)JNI_ktb_cipher_finalise },
	{ "ktb_cipher_get_mac", "(J)[B", (void *)JNI_ktb_cipher_get_mac },
	{ "ktb_cipher_get_data_size", "(J)J", (void *)JNI_ktb_cipher_get_data_size },
	{ "ktb_cipher_get_name_from_algo", "(LArcanaJNI$ktb_cipher_algo_t;)Ljava/lang/String;", (void *)JNI_ktb_cipher_get_name_from_algo },
	{ "ktb_cipher_get_name_from_mode", "(LArcanaJNI$ktb_cipher_mode_t;)Ljava/lang/String;", (void *)JNI_ktb_cipher_get_name_from_mode },
	{ "ktb_cipher_get_key_len", "(J)J", (void *)JNI_ktb_cipher_get_key_len },
	{ "ktb_cipher_get_block_len", "(J)J", (void *)JNI_ktb_cipher_get_block_len },
	{ "ktb_cipher_get_iv_len", "(J)J", (void *)JNI_ktb_cipher_get_iv_len },
	{ "ktb_cipher_get_mac_size", "(J)J", (void *)JNI_ktb_cipher_get_mac_size },
	{ "ktb_cipher_get_iv_len_from_mode", "(LArcanaJNI$ktb_cipher_mode_t;)J", (void *)JNI_ktb_cipher_get_iv_len_from_mode },
	{ "ktb_hash_init", "(LArcanaJNI$AddressWrapper;LArcanaJNI$ktb_hash_algo_t;)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_hash_init },
	{ "ktb_hash_init_hmac", "(LArcanaJNI$AddressWrapper;LArcanaJNI$ktb_hash_algo_t;[B)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_hash_init_hmac },
	{ "ktb_hash_clear", "(J)V", (void *)JNI_ktb_hash_clear },
	{ "ktb_hash_reset", "(J)V", (void *)JNI_ktb_hash_reset },
	{ "ktb_hash_process", "(J[B)V", (void *)JNI_ktb_hash_process },
	{ "ktb_hash_finalise", "(J)V", (void *)JNI_ktb_hash_finalise },
	{ "ktb_hash_retrieve", "(J)[B", (void *)JNI_ktb_hash_retrieve },
	{ "ktb_hash_get_name", "(J)Ljava/lang/String;", (void *)JNI_ktb_hash_get_name },
	{ "ktb_hash_get_name_from_algo", "(LArcanaJNI$ktb_hash_algo_t;)Ljava/lang/String;", (void *)JNI_ktb_hash_get_name_from_algo },
	{ "ktb_hash_get_len", "(J)J", (void *)JNI_ktb_hash_get_len },
	{ "ktb_hash_get_len_from_algo", "(LArcanaJNI$ktb_hash_algo_t;)J", (void *)JNI_ktb_hash_get_len_from_algo },
	{ "ktb_hash_get_block_size", "(J)J", (void *)JNI_ktb_hash_get_block_size },
	{ "ktb_hash_block", "(LArcanaJNI$ktb_hash_algo_t;[B[B)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_hash_block },
	{ "ktb_curves_count", "()I", (void *)JNI_ktb_curves_count },
	{ "ktb_curves_id", "(I)Ljava/lang/String;", (void *)JNI_ktb_curves_id },
	{ "ktb_base64_encode_size", "(J)J", (void *)JNI_ktb_base64_encode_size },
	{ "ktb_base64_encode", "([B[B)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_base64_encode },
	{ "ktb_base64_decode_size", "([B)J", (void *)JNI_ktb_base64_decode_size },
	{ "ktb_base64_decode", "([B[B)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_base64_decode }};

static int method_table_size = sizeof(method_table) / sizeof(method_table[0]);

jint JNI_OnLoad (JavaVM *vm, void *reserved) {
	JNIEnv *env;
	if ((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_6) != JNI_OK) {
			return JNI_ERR;
	} else {
		jclass class = (*env)->FindClass(env, "ArcanaJNI");
		if (class) {
			jint ret = (*env)->RegisterNatives(env, class, method_table, method_table_size);
			(*env)->DeleteLocalRef(env, class);
			return ret == 0 ? JNI_VERSION_1_6 : JNI_ERR;
		} else {
			return JNI_ERR;
		}
	}
}

