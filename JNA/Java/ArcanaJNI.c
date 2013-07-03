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


	typedef struct
	{
		void *ctxRef;
		JNIEnv *env;
	} contextWrapper;

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

		ktb_sign_ctx_t C_ctx = (ktb_sign_ctx_t)((contextWrapper *)ctx)->ctxRef;
		((contextWrapper *)ctx)->env = env;

		  ktb_sign_clear (C_ctx);

	}

	JNIEXPORT jobject JNICALL JNI_ktb_sign_reset(JNIEnv *env, jclass cls, jlong ctx) {

		jobject JNI_result;

		ktb_sign_ctx_t C_ctx = (ktb_sign_ctx_t)((contextWrapper *)ctx)->ctxRef;
		((contextWrapper *)ctx)->env = env;

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

	JNIEXPORT jobject JNICALL JNI_ktb_sign_process(JNIEnv *env, jclass cls, jlong ctx,jbyteArray data,jlong data_size) {

		jobject JNI_result;

		ktb_sign_ctx_t C_ctx = (ktb_sign_ctx_t)((contextWrapper *)ctx)->ctxRef;
		((contextWrapper *)ctx)->env = env;

		jbyte * C_data;
		int C_data_length = (*env)->GetArrayLength(env, data);
		C_data = (jbyte *)malloc(C_data_length);
		C_data = (*env)->GetByteArrayElements(env, data, NULL);

		jlong C_data_size = (jlong) data_size;

		ktb_errno tempJNI_result = ktb_sign_process (C_ctx, C_data, C_data_size);

		(*env)->SetByteArrayRegion(env, data, 0, C_data_length, C_data);
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

		ktb_sign_ctx_t C_ctx = (ktb_sign_ctx_t)((contextWrapper *)ctx)->ctxRef;
		((contextWrapper *)ctx)->env = env;

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

		ktb_sign_ctx_t C_ctx = (ktb_sign_ctx_t)((contextWrapper *)ctx)->ctxRef;
		((contextWrapper *)ctx)->env = env;

		const_ktb_public_key_t C_public_key = (const_ktb_public_key_t)((contextWrapper *)public_key)->ctxRef;
		((contextWrapper *)public_key)->env = env;

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

	JNIEXPORT jobject JNICALL JNI_ktb_sign_verify(JNIEnv *env, jclass cls, jlong ctx,jbyteArray signature,jlong signature_size,jobject is_valid) {

		jobject JNI_result;

		ktb_sign_ctx_t C_ctx = (ktb_sign_ctx_t)((contextWrapper *)ctx)->ctxRef;
		((contextWrapper *)ctx)->env = env;

		jbyte * C_signature;
		int C_signature_length = (*env)->GetArrayLength(env, signature);
		C_signature = (jbyte *)malloc(C_signature_length);
		C_signature = (*env)->GetByteArrayElements(env, signature, NULL);

		jlong C_signature_size = (jlong) signature_size;

		bool C_is_valid;

		ktb_errno tempJNI_result = ktb_sign_verify (C_ctx, C_signature, C_signature_size, &C_is_valid);

		(*env)->SetByteArrayRegion(env, signature, 0, C_signature_length, C_signature);
		free(C_signature);

		jclass boolWrp;
		jmethodID setVal;
		jboolean arg;
		boolWrp = (*env)->GetObjectClass(env, is_valid);
		setVal = (*env)->GetMethodID(env, boolWrp, "setValue", "(Z)V");
		arg = (jboolean) C_is_valid;
		(*env)->CallVoidMethod(is_valid, setVal, arg);

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

	JNIEXPORT jobject JNICALL JNI_ktb_sign_verify_block(JNIEnv *env, jclass cls, jobject algo,jlong public_key,jbyteArray data,jlong data_size,jbyteArray signature,jlong signature_size,jobject is_valid) {

		jobject JNI_result;

		jclass enm_algo;
		enm_algo = (*env)->GetObjectClass(env, algo);
		jmethodID get_algo = (*env)->GetMethodID(env, enm_algo, "getValue", "()I");
		jint algo_value = (*env)->CallIntMethod(env, algo, get_algo);
		ktb_hash_algo_t C_algo = (ktb_hash_algo_t)algo_value;

		const_ktb_public_key_t C_public_key = (const_ktb_public_key_t)((contextWrapper *)public_key)->ctxRef;
		((contextWrapper *)public_key)->env = env;

		jbyte * C_data;
		int C_data_length = (*env)->GetArrayLength(env, data);
		C_data = (jbyte *)malloc(C_data_length);
		C_data = (*env)->GetByteArrayElements(env, data, NULL);

		jlong C_data_size = (jlong) data_size;

		jbyte * C_signature;
		int C_signature_length = (*env)->GetArrayLength(env, signature);
		C_signature = (jbyte *)malloc(C_signature_length);
		C_signature = (*env)->GetByteArrayElements(env, signature, NULL);

		jlong C_signature_size = (jlong) signature_size;

		bool C_is_valid;

		ktb_errno tempJNI_result = ktb_sign_verify_block (C_algo, C_public_key, C_data, C_data_size, C_signature, C_signature_size, &C_is_valid);

		(*env)->SetByteArrayRegion(env, signature, 0, C_signature_length, C_signature);
		free(C_signature);

		(*env)->SetByteArrayRegion(env, signature, 0, C_signature_length, C_signature);
		free(C_signature);

		jclass boolWrp;
		jmethodID setVal;
		jboolean arg;
		boolWrp = (*env)->GetObjectClass(env, is_valid);
		setVal = (*env)->GetMethodID(env, boolWrp, "setValue", "(Z)V");
		arg = (jboolean) C_is_valid;
		(*env)->CallVoidMethod(is_valid, setVal, arg);

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

		ktb_sign_ctx_t C_ctx = (ktb_sign_ctx_t)((contextWrapper *)ctx)->ctxRef;
		((contextWrapper *)ctx)->env = env;

		const_ktb_private_key_t C_private_key = (const_ktb_private_key_t)((contextWrapper *)private_key)->ctxRef;
		((contextWrapper *)private_key)->env = env;

		ktb_prng_t C_prng = (ktb_prng_t)((contextWrapper *)prng)->ctxRef;
		((contextWrapper *)prng)->env = env;

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

		ktb_sign_ctx_t C_ctx = (ktb_sign_ctx_t)((contextWrapper *)ctx)->ctxRef;
		((contextWrapper *)ctx)->env = env;

		 JNI_result = ktb_sign_get_sign_size (C_ctx);

		 return JNI_result;
	}

	JNIEXPORT jbyteArray JNICALL JNI_ktb_sign_get_sign(JNIEnv *env, jclass cls, jlong ctx) {

		jbyteArray JNI_result;

		ktb_sign_ctx_t C_ctx = (ktb_sign_ctx_t)((contextWrapper *)ctx)->ctxRef;
		((contextWrapper *)ctx)->env = env;

		size_t C_size;

		void* tempJNI_result = (void*)ktb_sign_get_sign (C_ctx, &C_size);

		JNI_result = (*env)->NewByteArray(env, C_size);
		(*env)->SetByteArrayRegion(env, JNI_result, 0, C_size, (jbyte *)tempJNI_result);
		return JNI_result;
	}

	JNIEXPORT jlong JNICALL JNI_ktb_sign_get_sign_size_from_key(JNIEnv *env, jclass cls, jlong private_key) {

		jlong JNI_result;

		const_ktb_private_key_t C_private_key = (const_ktb_private_key_t)((contextWrapper *)private_key)->ctxRef;
		((contextWrapper *)private_key)->env = env;

		 JNI_result = ktb_sign_get_sign_size_from_key (C_private_key);

		 return JNI_result;
	}

	JNIEXPORT jobject JNICALL JNI_ktb_sign_sign_block(JNIEnv *env, jclass cls, jobject algo,jlong prng,jlong private_key,jbyteArray data,jlong data_size,jbyteArray signature,jlong signature_size) {

		jobject JNI_result;

		jclass enm_algo;
		enm_algo = (*env)->GetObjectClass(env, algo);
		jmethodID get_algo = (*env)->GetMethodID(env, enm_algo, "getValue", "()I");
		jint algo_value = (*env)->CallIntMethod(env, algo, get_algo);
		ktb_hash_algo_t C_algo = (ktb_hash_algo_t)algo_value;

		ktb_prng_t C_prng = (ktb_prng_t)((contextWrapper *)prng)->ctxRef;
		((contextWrapper *)prng)->env = env;

		const_ktb_private_key_t C_private_key = (const_ktb_private_key_t)((contextWrapper *)private_key)->ctxRef;
		((contextWrapper *)private_key)->env = env;

		jbyte * C_data;
		int C_data_length = (*env)->GetArrayLength(env, data);
		C_data = (jbyte *)malloc(C_data_length);
		C_data = (*env)->GetByteArrayElements(env, data, NULL);

		jlong C_data_size = (jlong) data_size;

		jbyte * C_signature;
		int C_signature_length = (*env)->GetArrayLength(env, signature);
		C_signature = (jbyte *)malloc(C_signature_length);
		C_signature = (*env)->GetByteArrayElements(env, signature, NULL);

		jlong C_signature_size = (jlong) signature_size;

		ktb_errno tempJNI_result = ktb_sign_sign_block (C_algo, C_prng, C_private_key, C_data, C_data_size, C_signature, C_signature_size);

		(*env)->SetByteArrayRegion(env, data, 0, C_data_length, C_data);
		free(C_data);

		(*env)->SetByteArrayRegion(env, signature, 0, C_signature_length, C_signature);
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

	JNIEXPORT jobject JNICALL JNI_ktb_kdf(JNIEnv *env, jclass cls, jobject algo,jbyteArray seed,jlong seed_size,jbyteArray derived_key,jlong derived_key_size) {

		jobject JNI_result;

		jclass enm_algo;
		enm_algo = (*env)->GetObjectClass(env, algo);
		jmethodID get_algo = (*env)->GetMethodID(env, enm_algo, "getValue", "()I");
		jint algo_value = (*env)->CallIntMethod(env, algo, get_algo);
		ktb_hash_algo_t C_algo = (ktb_hash_algo_t)algo_value;

		jbyte * C_seed;
		int C_seed_length = (*env)->GetArrayLength(env, seed);
		C_seed = (jbyte *)malloc(C_seed_length);
		C_seed = (*env)->GetByteArrayElements(env, seed, NULL);

		jlong C_seed_size = (jlong) seed_size;

		jbyte * C_derived_key;
		int C_derived_key_length = (*env)->GetArrayLength(env, derived_key);
		C_derived_key = (jbyte *)malloc(C_derived_key_length);
		C_derived_key = (*env)->GetByteArrayElements(env, derived_key, NULL);

		jlong C_derived_key_size = (jlong) derived_key_size;

		ktb_errno tempJNI_result = ktb_kdf (C_algo, C_seed, C_seed_size, C_derived_key, C_derived_key_size);

		(*env)->SetByteArrayRegion(env, seed, 0, C_seed_length, C_seed);
		free(C_seed);

		(*env)->SetByteArrayRegion(env, derived_key, 0, C_derived_key_length, C_derived_key);
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

	JNIEXPORT jobject JNICALL JNI_ktb_pbkdf(JNIEnv *env, jclass cls, jobject algo,jbyteArray passwd,jlong passwd_size,jbyteArray salt,jlong salt_size,jlong iteration_count,jbyteArray derived_key,jlong derived_key_size) {

		jobject JNI_result;

		jclass enm_algo;
		enm_algo = (*env)->GetObjectClass(env, algo);
		jmethodID get_algo = (*env)->GetMethodID(env, enm_algo, "getValue", "()I");
		jint algo_value = (*env)->CallIntMethod(env, algo, get_algo);
		ktb_hash_algo_t C_algo = (ktb_hash_algo_t)algo_value;

		jbyte * C_passwd;
		int C_passwd_length = (*env)->GetArrayLength(env, passwd);
		C_passwd = (jbyte *)malloc(C_passwd_length);
		C_passwd = (*env)->GetByteArrayElements(env, passwd, NULL);

		jlong C_passwd_size = (jlong) passwd_size;

		jbyte * C_salt;
		int C_salt_length = (*env)->GetArrayLength(env, salt);
		C_salt = (jbyte *)malloc(C_salt_length);
		C_salt = (*env)->GetByteArrayElements(env, salt, NULL);

		jlong C_salt_size = (jlong) salt_size;

		jlong C_iteration_count = (jlong) iteration_count;

		jbyte * C_derived_key;
		int C_derived_key_length = (*env)->GetArrayLength(env, derived_key);
		C_derived_key = (jbyte *)malloc(C_derived_key_length);
		C_derived_key = (*env)->GetByteArrayElements(env, derived_key, NULL);

		jlong C_derived_key_size = (jlong) derived_key_size;

		ktb_errno tempJNI_result = ktb_pbkdf (C_algo, C_passwd, C_passwd_size, C_salt, C_salt_size, C_iteration_count, C_derived_key, C_derived_key_size);

		(*env)->SetByteArrayRegion(env, salt, 0, C_salt_length, C_salt);
		free(C_salt);

		(*env)->SetByteArrayRegion(env, salt, 0, C_salt_length, C_salt);
		free(C_salt);

		(*env)->SetByteArrayRegion(env, derived_key, 0, C_derived_key_length, C_derived_key);
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

	JNIEXPORT jlong JNICALL JNI_ktb_kem_psec_encrypt_size(JNIEnv *env, jclass cls, jlong peer_public_key) {

		jlong JNI_result;

		const_ktb_public_key_t C_peer_public_key = (const_ktb_public_key_t)((contextWrapper *)peer_public_key)->ctxRef;
		((contextWrapper *)peer_public_key)->env = env;

		 JNI_result = ktb_kem_psec_encrypt_size (C_peer_public_key);

		 return JNI_result;
	}

	JNIEXPORT jobject JNICALL JNI_ktb_kem_psec_encrypt(JNIEnv *env, jclass cls, jobject algo,jlong prng,jlong peer_public_key,jbyteArray secret_key,jlong secret_key_size,jbyteArray ciphertext,jlong ciphertext_size) {

		jobject JNI_result;

		jclass enm_algo;
		enm_algo = (*env)->GetObjectClass(env, algo);
		jmethodID get_algo = (*env)->GetMethodID(env, enm_algo, "getValue", "()I");
		jint algo_value = (*env)->CallIntMethod(env, algo, get_algo);
		ktb_hash_algo_t C_algo = (ktb_hash_algo_t)algo_value;

		ktb_prng_t C_prng = (ktb_prng_t)((contextWrapper *)prng)->ctxRef;
		((contextWrapper *)prng)->env = env;

		const_ktb_public_key_t C_peer_public_key = (const_ktb_public_key_t)((contextWrapper *)peer_public_key)->ctxRef;
		((contextWrapper *)peer_public_key)->env = env;

		jbyte * C_secret_key;
		int C_secret_key_length = (*env)->GetArrayLength(env, secret_key);
		C_secret_key = (jbyte *)malloc(C_secret_key_length);
		C_secret_key = (*env)->GetByteArrayElements(env, secret_key, NULL);

		jlong C_secret_key_size = (jlong) secret_key_size;

		jbyte * C_ciphertext;
		int C_ciphertext_length = (*env)->GetArrayLength(env, ciphertext);
		C_ciphertext = (jbyte *)malloc(C_ciphertext_length);
		C_ciphertext = (*env)->GetByteArrayElements(env, ciphertext, NULL);

		jlong C_ciphertext_size = (jlong) ciphertext_size;

		ktb_errno tempJNI_result = ktb_kem_psec_encrypt (C_algo, C_prng, C_peer_public_key, C_secret_key, C_secret_key_size, C_ciphertext, C_ciphertext_size);

		(*env)->SetByteArrayRegion(env, ciphertext, 0, C_ciphertext_length, C_ciphertext);
		free(C_ciphertext);

		(*env)->SetByteArrayRegion(env, ciphertext, 0, C_ciphertext_length, C_ciphertext);
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

	JNIEXPORT jobject JNICALL JNI_ktb_kem_psec_decrypt(JNIEnv *env, jclass cls, jobject algo,jlong self_private_key,jbyteArray input_ciphertext,jlong input_ciphertext_size,jbyteArray secret_key,jlong secret_key_size) {

		jobject JNI_result;

		jclass enm_algo;
		enm_algo = (*env)->GetObjectClass(env, algo);
		jmethodID get_algo = (*env)->GetMethodID(env, enm_algo, "getValue", "()I");
		jint algo_value = (*env)->CallIntMethod(env, algo, get_algo);
		ktb_hash_algo_t C_algo = (ktb_hash_algo_t)algo_value;

		const_ktb_private_key_t C_self_private_key = (const_ktb_private_key_t)((contextWrapper *)self_private_key)->ctxRef;
		((contextWrapper *)self_private_key)->env = env;

		jbyte * C_input_ciphertext;
		int C_input_ciphertext_length = (*env)->GetArrayLength(env, input_ciphertext);
		C_input_ciphertext = (jbyte *)malloc(C_input_ciphertext_length);
		C_input_ciphertext = (*env)->GetByteArrayElements(env, input_ciphertext, NULL);

		jlong C_input_ciphertext_size = (jlong) input_ciphertext_size;

		jbyte * C_secret_key;
		int C_secret_key_length = (*env)->GetArrayLength(env, secret_key);
		C_secret_key = (jbyte *)malloc(C_secret_key_length);
		C_secret_key = (*env)->GetByteArrayElements(env, secret_key, NULL);

		jlong C_secret_key_size = (jlong) secret_key_size;

		ktb_errno tempJNI_result = ktb_kem_psec_decrypt (C_algo, C_self_private_key, C_input_ciphertext, C_input_ciphertext_size, C_secret_key, C_secret_key_size);

		(*env)->SetByteArrayRegion(env, input_ciphertext, 0, C_input_ciphertext_length, C_input_ciphertext);
		free(C_input_ciphertext);

		(*env)->SetByteArrayRegion(env, secret_key, 0, C_secret_key_length, C_secret_key);
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

		ktb_prng_t C_prng = (ktb_prng_t)((contextWrapper *)prng)->ctxRef;
		((contextWrapper *)prng)->env = env;

		  ktb_prng_clear (C_prng);

	}

	JNIEXPORT jobject JNICALL JNI_ktb_prng_reseed_with(JNIEnv *env, jclass cls, jlong prng,jbyteArray buffer,jlong buffer_size) {

		jobject JNI_result;

		ktb_prng_t C_prng = (ktb_prng_t)((contextWrapper *)prng)->ctxRef;
		((contextWrapper *)prng)->env = env;

		jbyte * C_buffer;
		int C_buffer_length = (*env)->GetArrayLength(env, buffer);
		C_buffer = (jbyte *)malloc(C_buffer_length);
		C_buffer = (*env)->GetByteArrayElements(env, buffer, NULL);

		jlong C_buffer_size = (jlong) buffer_size;

		ktb_errno tempJNI_result = ktb_prng_reseed_with (C_prng, C_buffer, C_buffer_size);

		(*env)->SetByteArrayRegion(env, buffer, 0, C_buffer_length, C_buffer);
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

		ktb_prng_t C_prng = (ktb_prng_t)((contextWrapper *)prng)->ctxRef;
		((contextWrapper *)prng)->env = env;

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

	JNIEXPORT jobject JNICALL JNI_ktb_prng_fill_buffer(JNIEnv *env, jclass cls, jlong prng,jbyteArray buffer,jlong buffer_size) {

		jobject JNI_result;
      ktb_prng_t C_prng;
      if(prng != 0) {
		   C_prng = (ktb_prng_t)((contextWrapper *)prng)->ctxRef;
		   ((contextWrapper *)prng)->env = env;
      }
      else {
         C_prng = NULL;
      }

		jbyte * C_buffer;
		int C_buffer_length = (*env)->GetArrayLength(env, buffer);
		C_buffer = (jbyte *)malloc(C_buffer_length);
		C_buffer = (*env)->GetByteArrayElements(env, buffer, NULL);

		jlong C_buffer_size = (jlong) buffer_size;

		ktb_errno tempJNI_result = ktb_prng_fill_buffer (C_prng, C_buffer, C_buffer_size);

		(*env)->SetByteArrayRegion(env, buffer, 0, C_buffer_length, C_buffer);
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

		ktb_public_key_t C_key = (ktb_public_key_t)((contextWrapper *)key)->ctxRef;
		((contextWrapper *)key)->env = env;

		  ktb_keys_public_key_clear (C_key);

	}

	JNIEXPORT void JNICALL JNI_ktb_keys_private_key_clear(JNIEnv *env, jclass cls, jlong key) {

		ktb_private_key_t C_key = (ktb_private_key_t)((contextWrapper *)key)->ctxRef;
		((contextWrapper *)key)->env = env;

		  ktb_keys_private_key_clear (C_key);

	}

	JNIEXPORT jlong JNICALL JNI_ktb_keys_public_key_export_size(JNIEnv *env, jclass cls, jlong public_key) {

		jlong JNI_result;

		const_ktb_public_key_t C_public_key = (const_ktb_public_key_t)((contextWrapper *)public_key)->ctxRef;
		((contextWrapper *)public_key)->env = env;

		 JNI_result = ktb_keys_public_key_export_size (C_public_key);

		 return JNI_result;
	}

	JNIEXPORT jobject JNICALL JNI_ktb_keys_public_key_export(JNIEnv *env, jclass cls, jlong public_key,jbyteArray result,jlong result_size) {

		jobject JNI_result;

		const_ktb_public_key_t C_public_key = (const_ktb_public_key_t)((contextWrapper *)public_key)->ctxRef;
		((contextWrapper *)public_key)->env = env;

		jbyte * C_result;
		int C_result_length = (*env)->GetArrayLength(env, result);
		C_result = (jbyte *)malloc(C_result_length);
		C_result = (*env)->GetByteArrayElements(env, result, NULL);

		jlong C_result_size = (jlong) result_size;

		ktb_errno tempJNI_result = ktb_keys_public_key_export (C_public_key, C_result, C_result_size);

		(*env)->SetByteArrayRegion(env, result, 0, C_result_length, C_result);
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

	JNIEXPORT jobject JNICALL JNI_ktb_keys_public_key_import(JNIEnv *env, jclass cls, jbyteArray public_key_bytes,jlong public_key_bytes_size,jobject public_key) {

		jobject JNI_result;

		jbyte * C_public_key_bytes;
		int C_public_key_bytes_length = (*env)->GetArrayLength(env, public_key_bytes);
		C_public_key_bytes = (jbyte *)malloc(C_public_key_bytes_length);
		C_public_key_bytes = (*env)->GetByteArrayElements(env, public_key_bytes, NULL);

		jlong C_public_key_bytes_size = (jlong) public_key_bytes_size;

		ktb_public_key_t C_public_key;
		contextWrapper *ctxWrp1 = (contextWrapper *)malloc(sizeof(contextWrapper));
		ctxWrp1->env = env;

		ktb_errno tempJNI_result = ktb_keys_public_key_import (C_public_key_bytes, C_public_key_bytes_size, &C_public_key);

		(*env)->SetByteArrayRegion(env, public_key_bytes, 0, C_public_key_bytes_length, C_public_key_bytes);
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

		const_ktb_private_key_t C_key = (const_ktb_private_key_t)((contextWrapper *)key)->ctxRef;
		((contextWrapper *)key)->env = env;

		 JNI_result = ktb_keys_private_key_export_size (C_key);

		 return JNI_result;
	}

	JNIEXPORT jobject JNICALL JNI_ktb_keys_private_key_export(JNIEnv *env, jclass cls, jlong key,jbyteArray buffer,jlong buffer_size) {

		jobject JNI_result;

		const_ktb_private_key_t C_key = (const_ktb_private_key_t)((contextWrapper *)key)->ctxRef;
		((contextWrapper *)key)->env = env;

		jbyte * C_buffer;
		int C_buffer_length = (*env)->GetArrayLength(env, buffer);
		C_buffer = (jbyte *)malloc(C_buffer_length);
		C_buffer = (*env)->GetByteArrayElements(env, buffer, NULL);

		jlong C_buffer_size = (jlong) buffer_size;

		ktb_errno tempJNI_result = ktb_keys_private_key_export (C_key, C_buffer, C_buffer_size);

		(*env)->SetByteArrayRegion(env, buffer, 0, C_buffer_length, C_buffer);
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

	JNIEXPORT jobject JNICALL JNI_ktb_keys_private_key_import(JNIEnv *env, jclass cls, jbyteArray private_key_bytes,jlong private_key_bytes_size,jobject private_key) {

		jobject JNI_result;

		jbyte * C_private_key_bytes;
		int C_private_key_bytes_length = (*env)->GetArrayLength(env, private_key_bytes);
		C_private_key_bytes = (jbyte *)malloc(C_private_key_bytes_length);
		C_private_key_bytes = (*env)->GetByteArrayElements(env, private_key_bytes, NULL);

		jlong C_private_key_bytes_size = (jlong) private_key_bytes_size;

		ktb_private_key_t C_private_key;
		contextWrapper *ctxWrp1 = (contextWrapper *)malloc(sizeof(contextWrapper));
		ctxWrp1->env = env;

		ktb_errno tempJNI_result = ktb_keys_private_key_import (C_private_key_bytes, C_private_key_bytes_size, &C_private_key);

		(*env)->SetByteArrayRegion(env, private_key_bytes, 0, C_private_key_bytes_length, C_private_key_bytes);
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

		ktb_prng_t C_prng = (ktb_prng_t)((contextWrapper *)prng)->ctxRef;
		((contextWrapper *)prng)->env = env;

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

		jlong C_input_size = (jlong) input_size;

		 JNI_result = ktb_radix64_encode_size (C_input_size);

		 return JNI_result;
	}

	JNIEXPORT jobject JNICALL JNI_ktb_radix64_encode(JNIEnv *env, jclass cls, jbyteArray input,jlong input_size,jbyteArray result,jlong result_size) {

		jobject JNI_result;

		jbyte * C_input;
		int C_input_length = (*env)->GetArrayLength(env, input);
		C_input = (jbyte *)malloc(C_input_length);
		C_input = (*env)->GetByteArrayElements(env, input, NULL);

		jlong C_input_size = (jlong) input_size;

		jbyte * C_result;
		int C_result_length = (*env)->GetArrayLength(env, result);
		C_result = (jbyte *)malloc(C_result_length);
		C_result = (*env)->GetByteArrayElements(env, result, NULL);

		jlong C_result_size = (jlong) result_size;

		ktb_errno tempJNI_result = ktb_radix64_encode (C_input, C_input_size, C_result, C_result_size);

		(*env)->SetByteArrayRegion(env, input, 0, C_input_length, C_input);
		free(C_input);

		(*env)->SetByteArrayRegion(env, result, 0, C_result_length, C_result);
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

	JNIEXPORT jlong JNICALL JNI_ktb_radix64_decode_size(JNIEnv *env, jclass cls, jbyteArray input,jlong input_size) {

		jlong JNI_result;

		jbyte * C_input;
		int C_input_length = (*env)->GetArrayLength(env, input);
		C_input = (jbyte *)malloc(C_input_length);
		C_input = (*env)->GetByteArrayElements(env, input, NULL);

		jlong C_input_size = (jlong) input_size;

		 JNI_result = ktb_radix64_decode_size (C_input, C_input_size);

		(*env)->SetByteArrayRegion(env, input, 0, C_input_length, C_input);
		free(C_input);

		 return JNI_result;
	}

	JNIEXPORT jobject JNICALL JNI_ktb_radix64_decode(JNIEnv *env, jclass cls, jbyteArray input,jlong input_size,jbyteArray result,jlong result_size) {

		jobject JNI_result;

		jbyte * C_input;
		int C_input_length = (*env)->GetArrayLength(env, input);
		C_input = (jbyte *)malloc(C_input_length);
		C_input = (*env)->GetByteArrayElements(env, input, NULL);

		jlong C_input_size = (jlong) input_size;

		jbyte * C_result;
		int C_result_length = (*env)->GetArrayLength(env, result);
		C_result = (jbyte *)malloc(C_result_length);
		C_result = (*env)->GetByteArrayElements(env, result, NULL);

		jlong C_result_size = (jlong) result_size;

		ktb_errno tempJNI_result = ktb_radix64_decode (C_input, C_input_size, C_result, C_result_size);

		(*env)->SetByteArrayRegion(env, input, 0, C_input_length, C_input);
		free(C_input);

		(*env)->SetByteArrayRegion(env, result, 0, C_result_length, C_result);
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

	JNIEXPORT jobject JNICALL JNI_ktb_radix64_verify(JNIEnv *env, jclass cls, jbyteArray input,jlong input_size,jobject verified) {

		jobject JNI_result;

		jbyte * C_input;
		int C_input_length = (*env)->GetArrayLength(env, input);
		C_input = (jbyte *)malloc(C_input_length);
		C_input = (*env)->GetByteArrayElements(env, input, NULL);

		jlong C_input_size = (jlong) input_size;

		bool C_verified;

		ktb_errno tempJNI_result = ktb_radix64_verify (C_input, C_input_size, &C_verified);

		(*env)->SetByteArrayRegion(env, input, 0, C_input_length, C_input);
		free(C_input);

		jclass boolWrp;
		jmethodID setVal;
		jboolean arg;
		boolWrp = (*env)->GetObjectClass(env, verified);
		setVal = (*env)->GetMethodID(env, boolWrp, "setValue", "(Z)V");
		arg = (jboolean) C_verified;
		(*env)->CallVoidMethod(verified, setVal, arg);

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

		jboolean C_encryption = (jboolean) encryption;

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

		ktb_cipher_ctx_t C_ctx = (ktb_cipher_ctx_t)((contextWrapper *)ctx)->ctxRef;
		((contextWrapper *)ctx)->env = env;

		  ktb_cipher_clear (C_ctx);

	}

	JNIEXPORT void JNICALL JNI_ktb_cipher_reset(JNIEnv *env, jclass cls, jlong ctx) {

		ktb_cipher_ctx_t C_ctx = (ktb_cipher_ctx_t)((contextWrapper *)ctx)->ctxRef;
		((contextWrapper *)ctx)->env = env;

		  ktb_cipher_reset (C_ctx);

	}

	JNIEXPORT jobject JNICALL JNI_ktb_cipher_set_key(JNIEnv *env, jclass cls, jlong ctx,jbyteArray key,jlong key_size) {

		jobject JNI_result;

		ktb_cipher_ctx_t C_ctx = (ktb_cipher_ctx_t)((contextWrapper *)ctx)->ctxRef;
		((contextWrapper *)ctx)->env = env;

		jbyte * C_key;
		int C_key_length = (*env)->GetArrayLength(env, key);
		C_key = (jbyte *)malloc(C_key_length);
		C_key = (*env)->GetByteArrayElements(env, key, NULL);

		jlong C_key_size = (jlong) key_size;

		ktb_errno tempJNI_result = ktb_cipher_set_key (C_ctx, C_key, C_key_size);

		(*env)->SetByteArrayRegion(env, key, 0, C_key_length, C_key);
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

	JNIEXPORT jobject JNICALL JNI_ktb_cipher_set_iv(JNIEnv *env, jclass cls, jlong ctx,jbyteArray iv,jlong iv_size) {

		jobject JNI_result;

		ktb_cipher_ctx_t C_ctx = (ktb_cipher_ctx_t)((contextWrapper *)ctx)->ctxRef;
		((contextWrapper *)ctx)->env = env;

		jbyte * C_iv;
		int C_iv_length = (*env)->GetArrayLength(env, iv);
		C_iv = (jbyte *)malloc(C_iv_length);
		C_iv = (*env)->GetByteArrayElements(env, iv, NULL);

		jlong C_iv_size = (jlong) iv_size;

		ktb_errno tempJNI_result = ktb_cipher_set_iv (C_ctx, C_iv, C_iv_size);

		(*env)->SetByteArrayRegion(env, iv, 0, C_iv_length, C_iv);
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

	JNIEXPORT jobject JNICALL JNI_ktb_cipher_set_auth_data(JNIEnv *env, jclass cls, jlong ctx,jbyteArray auth_data,jlong auth_data_size) {

		jobject JNI_result;

		ktb_cipher_ctx_t C_ctx = (ktb_cipher_ctx_t)((contextWrapper *)ctx)->ctxRef;
		((contextWrapper *)ctx)->env = env;

		jbyte * C_auth_data;
		int C_auth_data_length = (*env)->GetArrayLength(env, auth_data);
		C_auth_data = (jbyte *)malloc(C_auth_data_length);
		C_auth_data = (*env)->GetByteArrayElements(env, auth_data, NULL);

		jlong C_auth_data_size = (jlong) auth_data_size;

		ktb_errno tempJNI_result = ktb_cipher_set_auth_data (C_ctx, C_auth_data, C_auth_data_size);

		(*env)->SetByteArrayRegion(env, auth_data, 0, C_auth_data_length, C_auth_data);
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

		ktb_cipher_ctx_t C_ctx = (ktb_cipher_ctx_t)((contextWrapper *)ctx)->ctxRef;
		((contextWrapper *)ctx)->env = env;

		 JNI_result = ktb_cipher_get_prefix_size (C_ctx);

		 return JNI_result;
	}

	JNIEXPORT jobject JNICALL JNI_ktb_cipher_get_prefix(JNIEnv *env, jclass cls, jlong ctx,jbyteArray prefix,jlong prefix_size) {

		jobject JNI_result;

		ktb_cipher_ctx_t C_ctx = (ktb_cipher_ctx_t)((contextWrapper *)ctx)->ctxRef;
		((contextWrapper *)ctx)->env = env;

		jbyte * C_prefix;
		int C_prefix_length = (*env)->GetArrayLength(env, prefix);
		C_prefix = (jbyte *)malloc(C_prefix_length);
		C_prefix = (*env)->GetByteArrayElements(env, prefix, NULL);

		jlong C_prefix_size = (jlong) prefix_size;

		ktb_errno tempJNI_result = ktb_cipher_get_prefix (C_ctx, C_prefix, C_prefix_size);

		(*env)->SetByteArrayRegion(env, prefix, 0, C_prefix_length, C_prefix);
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

	JNIEXPORT jobject JNICALL JNI_ktb_cipher_set_prefix(JNIEnv *env, jclass cls, jlong ctx,jbyteArray prefix,jlong prefix_size) {

		jobject JNI_result;

		ktb_cipher_ctx_t C_ctx = (ktb_cipher_ctx_t)((contextWrapper *)ctx)->ctxRef;
		((contextWrapper *)ctx)->env = env;

		jbyte * C_prefix;
		int C_prefix_length = (*env)->GetArrayLength(env, prefix);
		C_prefix = (jbyte *)malloc(C_prefix_length);
		C_prefix = (*env)->GetByteArrayElements(env, prefix, NULL);

		jlong C_prefix_size = (jlong) prefix_size;

		ktb_errno tempJNI_result = ktb_cipher_set_prefix (C_ctx, C_prefix, C_prefix_size);

		(*env)->SetByteArrayRegion(env, prefix, 0, C_prefix_length, C_prefix);
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

		ktb_cipher_ctx_t C_ctx = (ktb_cipher_ctx_t)((contextWrapper *)ctx)->ctxRef;
		((contextWrapper *)ctx)->env = env;

		 JNI_result = ktb_cipher_get_suffix_size (C_ctx);

		 return JNI_result;
	}

	JNIEXPORT jobject JNICALL JNI_ktb_cipher_get_suffix(JNIEnv *env, jclass cls, jlong ctx,jbyteArray suffix,jlong suffix_size) {

		jobject JNI_result;

		ktb_cipher_ctx_t C_ctx = (ktb_cipher_ctx_t)((contextWrapper *)ctx)->ctxRef;
		((contextWrapper *)ctx)->env = env;

		jbyte * C_suffix;
		int C_suffix_length = (*env)->GetArrayLength(env, suffix);
		C_suffix = (jbyte *)malloc(C_suffix_length);
		C_suffix = (*env)->GetByteArrayElements(env, suffix, NULL);

		jlong C_suffix_size = (jlong) suffix_size;

		ktb_errno tempJNI_result = ktb_cipher_get_suffix (C_ctx, C_suffix, C_suffix_size);

		(*env)->SetByteArrayRegion(env, suffix, 0, C_suffix_length, C_suffix);
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

	JNIEXPORT jobject JNICALL JNI_ktb_cipher_encrypt_block(JNIEnv *env, jclass cls, jlong ctx,jbyteArray in,jlong in_size,jbyteArray out,jlong out_size) {

		jobject JNI_result;

		ktb_cipher_ctx_t C_ctx = (ktb_cipher_ctx_t)((contextWrapper *)ctx)->ctxRef;
		((contextWrapper *)ctx)->env = env;

		jbyte * C_in;
		int C_in_length = (*env)->GetArrayLength(env, in);
		C_in = (jbyte *)malloc(C_in_length);
		C_in = (*env)->GetByteArrayElements(env, in, NULL);

		jlong C_in_size = (jlong) in_size;

		jbyte * C_out;
		int C_out_length = (*env)->GetArrayLength(env, out);
		C_out = (jbyte *)malloc(C_out_length);
		C_out = (*env)->GetByteArrayElements(env, out, NULL);

		jlong C_out_size = (jlong) out_size;

		ktb_errno tempJNI_result = ktb_cipher_encrypt_block (C_ctx, C_in, C_in_size, C_out, C_out_size);

		(*env)->SetByteArrayRegion(env, in, 0, C_in_length, C_in);
		free(C_in);

		(*env)->SetByteArrayRegion(env, out, 0, C_out_length, C_out);
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

	JNIEXPORT jobject JNICALL JNI_ktb_cipher_decrypt_block(JNIEnv *env, jclass cls, jlong ctx,jbyteArray in,jlong in_size,jbyteArray out,jlong out_size) {

		jobject JNI_result;

		ktb_cipher_ctx_t C_ctx = (ktb_cipher_ctx_t)((contextWrapper *)ctx)->ctxRef;
		((contextWrapper *)ctx)->env = env;

		jbyte * C_in;
		int C_in_length = (*env)->GetArrayLength(env, in);
		C_in = (jbyte *)malloc(C_in_length);
		C_in = (*env)->GetByteArrayElements(env, in, NULL);

		jlong C_in_size = (jlong) in_size;

		jbyte * C_out;
		int C_out_length = (*env)->GetArrayLength(env, out);
		C_out = (jbyte *)malloc(C_out_length);
		C_out = (*env)->GetByteArrayElements(env, out, NULL);

		jlong C_out_size = (jlong) out_size;

		ktb_errno tempJNI_result = ktb_cipher_decrypt_block (C_ctx, C_in, C_in_size, C_out, C_out_size);

		(*env)->SetByteArrayRegion(env, in, 0, C_in_length, C_in);
		free(C_in);

		(*env)->SetByteArrayRegion(env, out, 0, C_out_length, C_out);
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

		ktb_cipher_ctx_t C_ctx = (ktb_cipher_ctx_t)((contextWrapper *)ctx)->ctxRef;
		((contextWrapper *)ctx)->env = env;

		  ktb_cipher_finalise (C_ctx);

	}

	JNIEXPORT jbyteArray JNICALL JNI_ktb_cipher_get_mac(JNIEnv *env, jclass cls, jlong ctx) {

		jbyteArray JNI_result;

		ktb_cipher_ctx_t C_ctx = (ktb_cipher_ctx_t)((contextWrapper *)ctx)->ctxRef;
		((contextWrapper *)ctx)->env = env;

		size_t C_size;

		void* tempJNI_result = (void*)ktb_cipher_get_mac (C_ctx, &C_size);

		JNI_result = (*env)->NewByteArray(env, C_size);
		(*env)->SetByteArrayRegion(env, JNI_result, 0, C_size, (jbyte *)tempJNI_result);
		return JNI_result;
	}

	JNIEXPORT jlong JNICALL JNI_ktb_cipher_get_data_size(JNIEnv *env, jclass cls, jlong ctx) {

		jlong JNI_result;

		ktb_cipher_ctx_t C_ctx = (ktb_cipher_ctx_t)((contextWrapper *)ctx)->ctxRef;
		((contextWrapper *)ctx)->env = env;

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

		ktb_cipher_ctx_t C_ctx = (ktb_cipher_ctx_t)((contextWrapper *)ctx)->ctxRef;
		((contextWrapper *)ctx)->env = env;

		 JNI_result = ktb_cipher_get_key_len (C_ctx);

		 return JNI_result;
	}

	JNIEXPORT jlong JNICALL JNI_ktb_cipher_get_block_len(JNIEnv *env, jclass cls, jlong ctx) {

		jlong JNI_result;

		ktb_cipher_ctx_t C_ctx = (ktb_cipher_ctx_t)((contextWrapper *)ctx)->ctxRef;
		((contextWrapper *)ctx)->env = env;

		 JNI_result = ktb_cipher_get_block_len (C_ctx);

		 return JNI_result;
	}

	JNIEXPORT jlong JNICALL JNI_ktb_cipher_get_iv_len(JNIEnv *env, jclass cls, jlong ctx) {

		jlong JNI_result;

		ktb_cipher_ctx_t C_ctx = (ktb_cipher_ctx_t)((contextWrapper *)ctx)->ctxRef;
		((contextWrapper *)ctx)->env = env;

		 JNI_result = ktb_cipher_get_iv_len (C_ctx);

		 return JNI_result;
	}

	JNIEXPORT jlong JNICALL JNI_ktb_cipher_get_mac_size(JNIEnv *env, jclass cls, jlong ctx) {

		jlong JNI_result;

		ktb_cipher_ctx_t C_ctx = (ktb_cipher_ctx_t)((contextWrapper *)ctx)->ctxRef;
		((contextWrapper *)ctx)->env = env;

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

	JNIEXPORT jobject JNICALL JNI_ktb_hash_init_hmac(JNIEnv *env, jclass cls, jobject ctx,jobject algo,jbyteArray key,jlong key_size) {

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
		int C_key_length = (*env)->GetArrayLength(env, key);
		C_key = (jbyte *)malloc(C_key_length);
		C_key = (*env)->GetByteArrayElements(env, key, NULL);

		jlong C_key_size = (jlong) key_size;

		ktb_errno tempJNI_result = ktb_hash_init_hmac (&C_ctx, C_algo, C_key, C_key_size);

		ctxWrp2->ctxRef = C_ctx;
		jclass adrWrp_ctx;
		jmethodID setAddr_ctx;
		jlong arg_ctx;

		adrWrp_ctx = (*env)->GetObjectClass(env, ctx);
		setAddr_ctx = (*env)->GetMethodID(env, adrWrp_ctx, "setAddress", "(J)V");
		arg_ctx = (jlong) ctxWrp2;
		(*env)->CallVoidMethod(env, ctx, setAddr_ctx, arg_ctx);

		(*env)->SetByteArrayRegion(env, key, 0, C_key_length, C_key);
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

		ktb_hash_ctx_t C_ctx = (ktb_hash_ctx_t)((contextWrapper *)ctx)->ctxRef;
		((contextWrapper *)ctx)->env = env;

		  ktb_hash_clear (C_ctx);

	}

	JNIEXPORT void JNICALL JNI_ktb_hash_reset(JNIEnv *env, jclass cls, jlong ctx) {

		ktb_hash_ctx_t C_ctx = (ktb_hash_ctx_t)((contextWrapper *)ctx)->ctxRef;
		((contextWrapper *)ctx)->env = env;

		  ktb_hash_reset (C_ctx);

	}

	JNIEXPORT void JNICALL JNI_ktb_hash_process(JNIEnv *env, jclass cls, jlong ctx,jbyteArray buf,jlong buf_size) {

		ktb_hash_ctx_t C_ctx = (ktb_hash_ctx_t)((contextWrapper *)ctx)->ctxRef;
		((contextWrapper *)ctx)->env = env;

		jbyte * C_buf;
		int C_buf_length = (*env)->GetArrayLength(env, buf);
		C_buf = (jbyte *)malloc(C_buf_length);
		C_buf = (*env)->GetByteArrayElements(env, buf, NULL);

		jlong C_buf_size = (jlong) buf_size;

		  ktb_hash_process (C_ctx, C_buf, C_buf_size);

		(*env)->SetByteArrayRegion(env, buf, 0, C_buf_length, C_buf);
		free(C_buf);

	}

	JNIEXPORT void JNICALL JNI_ktb_hash_finalise(JNIEnv *env, jclass cls, jlong ctx) {

		ktb_hash_ctx_t C_ctx = (ktb_hash_ctx_t)((contextWrapper *)ctx)->ctxRef;
		((contextWrapper *)ctx)->env = env;

		  ktb_hash_finalise (C_ctx);

	}

	JNIEXPORT jbyteArray JNICALL JNI_ktb_hash_retrieve(JNIEnv *env, jclass cls, jlong ctx,jlong size) {

		jbyteArray JNI_result;

		ktb_hash_ctx_t C_ctx = (ktb_hash_ctx_t)((contextWrapper *)ctx)->ctxRef;
		((contextWrapper *)ctx)->env = env;

		jlong C_size = (jlong) size;

		void* tempJNI_result = (void*)ktb_hash_retrieve (C_ctx, C_size);

		JNI_result = (*env)->NewByteArray(env, C_size);
		(*env)->SetByteArrayRegion(env, JNI_result, 0, C_size, (jbyte *)tempJNI_result);
		return JNI_result;
	}

	JNIEXPORT jstring JNICALL JNI_ktb_hash_get_name(JNIEnv *env, jclass cls, jlong ctx) {

		jstring JNI_result;

		ktb_hash_ctx_t C_ctx = (ktb_hash_ctx_t)((contextWrapper *)ctx)->ctxRef;
		((contextWrapper *)ctx)->env = env;

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

		ktb_hash_ctx_t C_ctx = (ktb_hash_ctx_t)((contextWrapper *)ctx)->ctxRef;
		((contextWrapper *)ctx)->env = env;

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

		ktb_hash_ctx_t C_ctx = (ktb_hash_ctx_t)((contextWrapper *)ctx)->ctxRef;
		((contextWrapper *)ctx)->env = env;

		 JNI_result = ktb_hash_get_block_size (C_ctx);

		 return JNI_result;
	}

	JNIEXPORT jobject JNICALL JNI_ktb_hash_block(JNIEnv *env, jclass cls, jobject algo,jbyteArray block,jlong block_size,jbyteArray result,jlong result_size) {

		jobject JNI_result;

		jclass enm_algo;
		enm_algo = (*env)->GetObjectClass(env, algo);
		jmethodID get_algo = (*env)->GetMethodID(env, enm_algo, "getValue", "()I");
		jint algo_value = (*env)->CallIntMethod(env, algo, get_algo);
		ktb_hash_algo_t C_algo = (ktb_hash_algo_t)algo_value;

		jbyte * C_block;
		int C_block_length = (*env)->GetArrayLength(env, block);
		C_block = (jbyte *)malloc(C_block_length);
		C_block = (*env)->GetByteArrayElements(env, block, NULL);

		jlong C_block_size = (jlong) block_size;

		jbyte * C_result;
		int C_result_length = (*env)->GetArrayLength(env, result);
		C_result = (jbyte *)malloc(C_result_length);
		C_result = (*env)->GetByteArrayElements(env, result, NULL);

		jlong C_result_size = (jlong) result_size;

		ktb_errno tempJNI_result = ktb_hash_block (C_algo, C_block, C_block_size, C_result, C_result_size);

		(*env)->SetByteArrayRegion(env, block, 0, C_block_length, C_block);
		free(C_block);

		(*env)->SetByteArrayRegion(env, result, 0, C_result_length, C_result);
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

		jint C_index = (jint) index;

		char * tempJNI_result = (char *)ktb_curves_id (C_index);

		JNI_result = (*env)->NewStringUTF(env, tempJNI_result);
		 return JNI_result;
	}

	JNIEXPORT jlong JNICALL JNI_ktb_base64_encode_size(JNIEnv *env, jclass cls, jlong input_size) {

		jlong JNI_result;

		jlong C_input_size = (jlong) input_size;

		 JNI_result = ktb_base64_encode_size (C_input_size);

		 return JNI_result;
	}

	JNIEXPORT jobject JNICALL JNI_ktb_base64_encode(JNIEnv *env, jclass cls, jbyteArray input,jlong input_size,jbyteArray result,jlong result_size) {

		jobject JNI_result;

		jbyte * C_input;
		int C_input_length = (*env)->GetArrayLength(env, input);
		C_input = (jbyte *)malloc(C_input_length);
		C_input = (*env)->GetByteArrayElements(env, input, NULL);

		jlong C_input_size = (jlong) input_size;

		jbyte * C_result;
		int C_result_length = (*env)->GetArrayLength(env, result);
		C_result = (jbyte *)malloc(C_result_length);
		C_result = (*env)->GetByteArrayElements(env, result, NULL);

		jlong C_result_size = (jlong) result_size;

		ktb_errno tempJNI_result = ktb_base64_encode (C_input, C_input_size, C_result, C_result_size);

		(*env)->SetByteArrayRegion(env, input, 0, C_input_length, C_input);
		free(C_input);

		(*env)->SetByteArrayRegion(env, result, 0, C_result_length, C_result);
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

	JNIEXPORT jlong JNICALL JNI_ktb_base64_decode_size(JNIEnv *env, jclass cls, jbyteArray input,jlong input_size) {

		jlong JNI_result;

		jbyte * C_input;
		int C_input_length = (*env)->GetArrayLength(env, input);
		C_input = (jbyte *)malloc(C_input_length);
		C_input = (*env)->GetByteArrayElements(env, input, NULL);

		jlong C_input_size = (jlong) input_size;

		 JNI_result = ktb_base64_decode_size (C_input, C_input_size);

		(*env)->SetByteArrayRegion(env, input, 0, C_input_length, C_input);
		free(C_input);

		 return JNI_result;
	}

	JNIEXPORT jobject JNICALL JNI_ktb_base64_decode(JNIEnv *env, jclass cls, jbyteArray input,jlong input_size,jbyteArray result,jlong result_size) {

		jobject JNI_result;

		jbyte * C_input;
		int C_input_length = (*env)->GetArrayLength(env, input);
		C_input = (jbyte *)malloc(C_input_length);
		C_input = (*env)->GetByteArrayElements(env, input, NULL);

		jlong C_input_size = (jlong) input_size;

		jbyte * C_result;
		int C_result_length = (*env)->GetArrayLength(env, result);
		C_result = (jbyte *)malloc(C_result_length);
		C_result = (*env)->GetByteArrayElements(env, result, NULL);

		jlong C_result_size = (jlong) result_size;

		ktb_errno tempJNI_result = ktb_base64_decode (C_input, C_input_size, C_result, C_result_size);

		(*env)->SetByteArrayRegion(env, input, 0, C_input_length, C_input);
		free(C_input);

		(*env)->SetByteArrayRegion(env, result, 0, C_result_length, C_result);
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

	JNIEXPORT jobject JNICALL JNI_ktb_kep_init(JNIEnv *env, jclass cls, jobject ctx,jlong prng,jobject algo,jlong algo_data,jlong algo_data_size,jstring curve_id,jobject hash_algo,jlong secret_key_size,jint peer_count) {

		jobject JNI_result;

		ktb_kep_ctx_t C_ctx;
		contextWrapper *ctxWrp1 = (contextWrapper *)malloc(sizeof(contextWrapper));
		ctxWrp1->env = env;

		ktb_prng_t C_prng = (ktb_prng_t)((contextWrapper *)prng)->ctxRef;
		((contextWrapper *)prng)->env = env;

		jclass enm_algo;
		enm_algo = (*env)->GetObjectClass(env, algo);
		jmethodID get_algo = (*env)->GetMethodID(env, enm_algo, "getValue", "()I");
		jint algo_value = (*env)->CallIntMethod(env, algo, get_algo);
		ktb_kep_algo_t C_algo = (ktb_kep_algo_t)algo_value;

		ktb_kep_algo_data_t C_algo_data = (ktb_kep_algo_data_t)((contextWrapper *)algo_data)->ctxRef;
		((contextWrapper *)algo_data)->env = env;

		jlong C_algo_data_size = (jlong) algo_data_size;

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

		jlong C_secret_key_size = (jlong) secret_key_size;

		jint C_peer_count = (jint) peer_count;

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

		ktb_kep_ctx_t C_ctx = (ktb_kep_ctx_t)((contextWrapper *)ctx)->ctxRef;
		((contextWrapper *)ctx)->env = env;

		  ktb_kep_clear (C_ctx);

	}

	JNIEXPORT jbyteArray JNICALL JNI_ktb_kep_get_data(JNIEnv *env, jclass cls, jlong ctx) {

		jbyteArray JNI_result;

		ktb_kep_ctx_t C_ctx = (ktb_kep_ctx_t)((contextWrapper *)ctx)->ctxRef;
		((contextWrapper *)ctx)->env = env;

		size_t C_size;

		void* tempJNI_result = (void*)ktb_kep_get_data (C_ctx, &C_size);

		JNI_result = (*env)->NewByteArray(env, C_size);
		(*env)->SetByteArrayRegion(env, JNI_result, 0, C_size, (jbyte *)tempJNI_result);
		return JNI_result;
	}

	JNIEXPORT jobject JNICALL JNI_ktb_kep_put_data(JNIEnv *env, jclass cls, jlong ctx,jbyteArray peer_data,jlong peer_data_size,jobject continue_exchange) {

		jobject JNI_result;

		ktb_kep_ctx_t C_ctx = (ktb_kep_ctx_t)((contextWrapper *)ctx)->ctxRef;
		((contextWrapper *)ctx)->env = env;

		jbyte * C_peer_data;
		int C_peer_data_length = (*env)->GetArrayLength(env, peer_data);
		C_peer_data = (jbyte *)malloc(C_peer_data_length);
		C_peer_data = (*env)->GetByteArrayElements(env, peer_data, NULL);

		jlong C_peer_data_size = (jlong) peer_data_size;

		bool C_continue_exchange;

		ktb_errno tempJNI_result = ktb_kep_put_data (C_ctx, C_peer_data, C_peer_data_size, &C_continue_exchange);

		(*env)->SetByteArrayRegion(env, peer_data, 0, C_peer_data_length, C_peer_data);
		free(C_peer_data);

		jclass boolWrp;
		jmethodID setVal;
		jboolean arg;
		boolWrp = (*env)->GetObjectClass(env, continue_exchange);
		setVal = (*env)->GetMethodID(env, boolWrp, "setValue", "(Z)V");
		arg = (jboolean) C_continue_exchange;
		(*env)->CallVoidMethod(continue_exchange, setVal, arg);

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

	JNIEXPORT jobject JNICALL JNI_ktb_kep_finalise(JNIEnv *env, jclass cls, jlong ctx,jbyteArray secret_key,jlong secret_key_size) {

		jobject JNI_result;

		ktb_kep_ctx_t C_ctx = (ktb_kep_ctx_t)((contextWrapper *)ctx)->ctxRef;
		((contextWrapper *)ctx)->env = env;

		jbyte * C_secret_key;
		int C_secret_key_length = (*env)->GetArrayLength(env, secret_key);
		C_secret_key = (jbyte *)malloc(C_secret_key_length);
		C_secret_key = (*env)->GetByteArrayElements(env, secret_key, NULL);

		jlong C_secret_key_size = (jlong) secret_key_size;

		ktb_errno tempJNI_result = ktb_kep_finalise (C_ctx, C_secret_key, C_secret_key_size);

		(*env)->SetByteArrayRegion(env, secret_key, 0, C_secret_key_length, C_secret_key);
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

static JNINativeMethod method_table[] = {
	{ "ktb_sign_init", "(LArcanaJNI$AddressWrapper;LArcanaJNI$ktb_hash_algo_t;)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_sign_init },
	{ "ktb_sign_clear", "(J)V", (void *)JNI_ktb_sign_clear },
	{ "ktb_sign_reset", "(J)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_sign_reset },
	{ "ktb_sign_process", "(J[BJ)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_sign_process },
	{ "ktb_sign_finalise", "(J)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_sign_finalise },
	{ "ktb_sign_set_public_key", "(JJ)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_sign_set_public_key },
	{ "ktb_sign_verify", "(J[BJLArcanaJNI$BoolWrapper;)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_sign_verify },
	{ "ktb_sign_verify_block", "(LArcanaJNI$ktb_hash_algo_t;J[BJ[BJLArcanaJNI$BoolWrapper;)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_sign_verify_block },
	{ "ktb_sign_set_private_key", "(JJJ)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_sign_set_private_key },
	{ "ktb_sign_get_sign_size", "(J)J", (void *)JNI_ktb_sign_get_sign_size },
	{ "ktb_sign_get_sign", "(J)[B", (void *)JNI_ktb_sign_get_sign },
	{ "ktb_sign_get_sign_size_from_key", "(J)J", (void *)JNI_ktb_sign_get_sign_size_from_key },
	{ "ktb_sign_sign_block", "(LArcanaJNI$ktb_hash_algo_t;JJ[BJ[BJ)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_sign_sign_block },
	{ "ktb_kdf", "(LArcanaJNI$ktb_hash_algo_t;[BJ[BJ)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_kdf },
	{ "ktb_pbkdf", "(LArcanaJNI$ktb_hash_algo_t;[BJ[BJJ[BJ)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_pbkdf },
	{ "ktb_kdf_max_size", "(LArcanaJNI$ktb_hash_algo_t;)J", (void *)JNI_ktb_kdf_max_size },
	{ "ktb_kem_psec_encrypt_size", "(J)J", (void *)JNI_ktb_kem_psec_encrypt_size },
	{ "ktb_kem_psec_encrypt", "(LArcanaJNI$ktb_hash_algo_t;JJ[BJ[BJ)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_kem_psec_encrypt },
	{ "ktb_kem_psec_decrypt", "(LArcanaJNI$ktb_hash_algo_t;J[BJ[BJ)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_kem_psec_decrypt },
	{ "ktb_prng_clear", "(J)V", (void *)JNI_ktb_prng_clear },
	{ "ktb_prng_reseed_with", "(J[BJ)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_prng_reseed_with },
	{ "ktb_prng_reseed", "(J)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_prng_reseed },
	{ "ktb_prng_fill_buffer", "(J[BJ)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_prng_fill_buffer },
	{ "ktb_keys_public_key_clear", "(J)V", (void *)JNI_ktb_keys_public_key_clear },
	{ "ktb_keys_private_key_clear", "(J)V", (void *)JNI_ktb_keys_private_key_clear },
	{ "ktb_keys_public_key_export_size", "(J)J", (void *)JNI_ktb_keys_public_key_export_size },
	{ "ktb_keys_public_key_export", "(J[BJ)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_keys_public_key_export },
	{ "ktb_keys_public_key_import", "([BJLArcanaJNI$AddressWrapper;)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_keys_public_key_import },
	{ "ktb_keys_private_key_export_size", "(J)J", (void *)JNI_ktb_keys_private_key_export_size },
	{ "ktb_keys_private_key_export", "(J[BJ)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_keys_private_key_export },
	{ "ktb_keys_private_key_import", "([BJLArcanaJNI$AddressWrapper;)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_keys_private_key_import },
	{ "ktb_keys_generate_keypair", "(JLjava/lang/String;LArcanaJNI$AddressWrapper;LArcanaJNI$AddressWrapper;)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_keys_generate_keypair },
	{ "ktb_radix64_encode_size", "(J)J", (void *)JNI_ktb_radix64_encode_size },
	{ "ktb_radix64_encode", "([BJ[BJ)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_radix64_encode },
	{ "ktb_radix64_decode_size", "([BJ)J", (void *)JNI_ktb_radix64_decode_size },
	{ "ktb_radix64_decode", "([BJ[BJ)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_radix64_decode },
	{ "ktb_radix64_verify", "([BJLArcanaJNI$BoolWrapper;)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_radix64_verify },
	{ "ktb_cipher_init", "(LArcanaJNI$AddressWrapper;LArcanaJNI$ktb_cipher_algo_t;LArcanaJNI$ktb_cipher_mode_t;Z)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_cipher_init },
	{ "ktb_cipher_clear", "(J)V", (void *)JNI_ktb_cipher_clear },
	{ "ktb_cipher_reset", "(J)V", (void *)JNI_ktb_cipher_reset },
	{ "ktb_cipher_set_key", "(J[BJ)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_cipher_set_key },
	{ "ktb_cipher_set_iv", "(J[BJ)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_cipher_set_iv },
	{ "ktb_cipher_set_auth_data", "(J[BJ)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_cipher_set_auth_data },
	{ "ktb_cipher_get_prefix_size", "(J)J", (void *)JNI_ktb_cipher_get_prefix_size },
	{ "ktb_cipher_get_prefix", "(J[BJ)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_cipher_get_prefix },
	{ "ktb_cipher_set_prefix", "(J[BJ)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_cipher_set_prefix },
	{ "ktb_cipher_get_suffix_size", "(J)J", (void *)JNI_ktb_cipher_get_suffix_size },
	{ "ktb_cipher_get_suffix", "(J[BJ)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_cipher_get_suffix },
	{ "ktb_cipher_encrypt_block", "(J[BJ[BJ)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_cipher_encrypt_block },
	{ "ktb_cipher_decrypt_block", "(J[BJ[BJ)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_cipher_decrypt_block },
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
	{ "ktb_hash_init_hmac", "(LArcanaJNI$AddressWrapper;LArcanaJNI$ktb_hash_algo_t;[BJ)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_hash_init_hmac },
	{ "ktb_hash_clear", "(J)V", (void *)JNI_ktb_hash_clear },
	{ "ktb_hash_reset", "(J)V", (void *)JNI_ktb_hash_reset },
	{ "ktb_hash_process", "(J[BJ)V", (void *)JNI_ktb_hash_process },
	{ "ktb_hash_finalise", "(J)V", (void *)JNI_ktb_hash_finalise },
	{ "ktb_hash_retrieve", "(JJ)[B", (void *)JNI_ktb_hash_retrieve },
	{ "ktb_hash_get_name", "(J)Ljava/lang/String;", (void *)JNI_ktb_hash_get_name },
	{ "ktb_hash_get_name_from_algo", "(LArcanaJNI$ktb_hash_algo_t;)Ljava/lang/String;", (void *)JNI_ktb_hash_get_name_from_algo },
	{ "ktb_hash_get_len", "(J)J", (void *)JNI_ktb_hash_get_len },
	{ "ktb_hash_get_len_from_algo", "(LArcanaJNI$ktb_hash_algo_t;)J", (void *)JNI_ktb_hash_get_len_from_algo },
	{ "ktb_hash_get_block_size", "(J)J", (void *)JNI_ktb_hash_get_block_size },
	{ "ktb_hash_block", "(LArcanaJNI$ktb_hash_algo_t;[BJ[BJ)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_hash_block },
	{ "ktb_curves_count", "()I", (void *)JNI_ktb_curves_count },
	{ "ktb_curves_id", "(I)Ljava/lang/String;", (void *)JNI_ktb_curves_id },
	{ "ktb_base64_encode_size", "(J)J", (void *)JNI_ktb_base64_encode_size },
	{ "ktb_base64_encode", "([BJ[BJ)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_base64_encode },
	{ "ktb_base64_decode_size", "([BJ)J", (void *)JNI_ktb_base64_decode_size },
	{ "ktb_base64_decode", "([BJ[BJ)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_base64_decode },
	{ "ktb_kep_init", "(LArcanaJNI$AddressWrapper;JLArcanaJNI$ktb_kep_algo_t;JJLjava/lang/String;LArcanaJNI$ktb_hash_algo_t;JI)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_kep_init },
	{ "ktb_kep_clear", "(J)V", (void *)JNI_ktb_kep_clear },
	{ "ktb_kep_get_data", "(J)[B", (void *)JNI_ktb_kep_get_data },
	{ "ktb_kep_put_data", "(J[BJLArcanaJNI$BoolWrapper;)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_kep_put_data },
	{ "ktb_kep_finalise", "(J[BJ)LArcanaJNI$ktb_errno;", (void *)JNI_ktb_kep_finalise },
	{ "ktb_kep_get_algo_name", "(LArcanaJNI$ktb_kep_algo_t;)Ljava/lang/String;", (void *)JNI_ktb_kep_get_algo_name },
	{ "ktb_init", "()LArcanaJNI$ktb_errno;", (void *)JNI_ktb_init },
	{ "ktb_clear", "()V", (void *)JNI_ktb_clear }};

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
