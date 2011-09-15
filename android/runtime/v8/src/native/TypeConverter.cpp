#include <jni.h>
#include <v8.h>

#include "TypeConverter.h"
#include "JNIUtil.h"

using namespace titanium;


/****************************** public methods ******************************/
jshort TypeConverter::jsNumberToJavaShort(v8::Handle<v8::Number> jsNumber)
{
	return ((jshort) jsNumber->Value());
}


v8::Handle<v8::Number> TypeConverter::javaShortToJsNumber(jshort javaShort)
{
	return v8::Number::New ((double) javaShort);
}


jint TypeConverter::jsNumberToJavaInt(v8::Handle<v8::Number> jsNumber)
{
	return ((jint) jsNumber->Value());
}


v8::Handle<v8::Number> TypeConverter::javaIntToJsNumber(jint javaInt)
{
	return v8::Number::New ((double) javaInt);
}


jlong TypeConverter::jsNumberToJavaLong(v8::Handle<v8::Number> jsNumber)
{
	return ((jlong) jsNumber->Value());
}


v8::Handle<v8::Number> TypeConverter::javaLongToJsNumber(jlong javaLong)
{
	return v8::Number::New ((double) javaLong);
}


jfloat TypeConverter::jsNumberToJavaFloat(v8::Handle<v8::Number> jsNumber)
{
	return ((jfloat) jsNumber->Value());
}


v8::Handle<v8::Number> TypeConverter::javaFloatToJsNumber(jfloat javaFloat)
{
	return v8::Number::New ((double) javaFloat);
}


jdouble TypeConverter::jsNumberToJavaDouble(v8::Handle<v8::Number> jsNumber)
{
	return ((jdouble) jsNumber->Value());
}


v8::Handle<v8::Number> TypeConverter::javaDoubleToJsNumber(jdouble javaDouble)
{
	return v8::Number::New (javaDouble);
}


jboolean TypeConverter::jsBooleanToJavaBoolean(v8::Handle<v8::Boolean> jsBoolean)
{
	return (jsBoolean->Value()) == JNI_TRUE;
}


v8::Handle<v8::Boolean> TypeConverter::javaBooleanToJsBoolean(jboolean javaBoolean)
{
	return v8::Boolean::New ((bool) javaBoolean);
}


jstring TypeConverter::jsStringToJavaString (v8::Handle<v8::String> jsString)
{
	JNIEnv *env = JNIUtil::getJNIEnv();
	if (env == NULL)
	{
		return NULL;
	}

	v8::String::Value javaString (jsString);
	return env->NewString (*javaString, javaString.length());
}


v8::Handle<v8::String> TypeConverter::javaStringToJsString(jstring javaString)
{
	JNIEnv *env = JNIUtil::getJNIEnv();
	if (env == NULL)
	{
		return v8::Handle<v8::String>();
	}

	const char *nativeString = env->GetStringUTFChars (javaString, 0);
	int nativeStringLength = env->GetStringUTFLength (javaString);

	v8::Handle<v8::String> jsString = v8::String::New (nativeString, nativeStringLength);
	env->ReleaseStringUTFChars (javaString, nativeString);

	return jsString;
}


jobject TypeConverter::jsDateToJavaDate(v8::Handle<v8::Date> jsDate)
{
	JNIEnv *env = JNIUtil::getJNIEnv();
	if (env == NULL)
	{
		return NULL;
	}

	return env->NewObject (JNIUtil::dateClass, JNIUtil::dateInitMethod, (jlong) jsDate->NumberValue());
}


jlong TypeConverter::jsDateToJavaLong(v8::Handle<v8::Date> jsDate)
{
	(jlong) jsDate->NumberValue();
}


v8::Handle<v8::Date> TypeConverter::javaDateToJsDate (jobject javaDate)
{
	JNIEnv *env = JNIUtil::getJNIEnv();
	if (env == NULL)
	{
		return v8::Handle<v8::Date>();
	}

	jlong epochTime = env->CallLongMethod (javaDate, JNIUtil::dateGetTimeMethod);
	return v8::Handle<v8::Date>::Cast (v8::Date::New ((double) epochTime));
}


v8::Handle<v8::Date> TypeConverter::javaLongToJsDate (jlong javaLong)
{
	return v8::Handle<v8::Date>::Cast (v8::Date::New ((double) javaLong));
}


jobject TypeConverter::getJavaUndefined()
{
	
}


jarray TypeConverter::jsArrayToJavaArray (v8::Handle<v8::Array> jsArray)
{
	JNIEnv *env = JNIUtil::getJNIEnv();
	if (env == NULL)
	{
		return NULL;
	}

	int arrayLength = jsArray->Length();
	jobjectArray javaArray = env->NewObjectArray (arrayLength, JNIUtil::objectClass, NULL);

	for (int i = 0; i < arrayLength; i++)
	{
		v8::Local<v8::Value> element = jsArray->Get (i);
		jobject javaObject = jsValueToJavaObject (element);
		env->SetObjectArrayElement (javaArray, i, javaObject);
	}

	return javaArray;
}


v8::Handle<v8::Array> TypeConverter::javaArrayToJsArray (jbooleanArray javaBooleanArray)
{
	JNIEnv *env = JNIUtil::getJNIEnv();
	if (env == NULL)
	{
		return v8::Handle<v8::Array>();
	}

	int arrayLength = env->GetArrayLength (javaBooleanArray);
	v8::Handle<v8::Array> jsArray = v8::Array::New (arrayLength);

	jboolean *arrayElements = env->GetBooleanArrayElements (javaBooleanArray, 0);
	for (int i = 0; i < arrayLength; i++)
	{
		jsArray->Set ((uint32_t)i, v8::Boolean::New (arrayElements [i]));
	}

	return jsArray;
}


v8::Handle<v8::Array> TypeConverter::javaArrayToJsArray (jshortArray javaShortArray)
{
	return javaDoubleArrayToJsNumberArray ((jdoubleArray) javaShortArray);
}


v8::Handle<v8::Array> TypeConverter::javaArrayToJsArray (jintArray javaIntArray)
{
	return javaDoubleArrayToJsNumberArray ((jdoubleArray) javaIntArray);
}


v8::Handle<v8::Array> TypeConverter::javaArrayToJsArray (jlongArray javaLongArray)
{
	return javaDoubleArrayToJsNumberArray ((jdoubleArray) javaLongArray);
}


v8::Handle<v8::Array> TypeConverter::javaArrayToJsArray (jfloatArray javaFloatArray)
{
	return javaDoubleArrayToJsNumberArray ((jdoubleArray) javaFloatArray);
}


v8::Handle<v8::Array> TypeConverter::javaArrayToJsArray (jdoubleArray javaDoubleArray)
{
	return javaDoubleArrayToJsNumberArray ((jdoubleArray) javaDoubleArray);
}


v8::Handle<v8::Array> TypeConverter::javaArrayToJsArray (jobjectArray javaObjectArray)
{
	JNIEnv *env = JNIUtil::getJNIEnv();
	if (env == NULL)
	{
		return v8::Handle<v8::Array>();
	}

	int arrayLength = env->GetArrayLength (javaObjectArray);
	v8::Handle<v8::Array> jsArray = v8::Array::New (arrayLength);

	for (int i = 0; i < arrayLength; i++)
	{
		TypeConverter::javaObjectToJsValue (env->GetObjectArrayElement (javaObjectArray, i));

		// will insert Handle<Object>
		//jsArray->Set ((uint32_t)i, v8::Value::New (env->GetObjectArrayElement (javaObjectArray, i)));
	}

	return jsArray;
}


// converts js value to java object and recursively converts sub objects if this
// object is a container type
jobject TypeConverter::jsValueToJavaObject (v8::Local<v8::Value> jsValue)
{
	JNIEnv *env = JNIUtil::getJNIEnv();
	if (env == NULL)
	{
		return NULL;
	}

	if (jsValue->IsNumber())
	{
		jdouble javaDouble = TypeConverter::jsNumberToJavaDouble (jsValue->ToNumber());
		return env->NewObject (JNIUtil::doubleClass, JNIUtil::doubleInitMethod, javaDouble);
	}
	else if (jsValue->IsBoolean())
	{
		jboolean javaBoolean = TypeConverter::jsBooleanToJavaBoolean (jsValue->ToBoolean());
		return env->NewObject (JNIUtil::booleanClass, JNIUtil::booleanInitMethod, javaBoolean);
	}
	else if (jsValue->IsString())
	{
		return TypeConverter::jsStringToJavaString (jsValue->ToString());
	}
	else if (jsValue->IsDate())
	{
		jlong javaLong = TypeConverter::jsDateToJavaLong (v8::Handle<v8::Date>::Cast (jsValue));
		return env->NewObject (JNIUtil::longClass, JNIUtil::longInitMethod, javaLong);
	}
	else if (jsValue->IsArray())
	{
		return TypeConverter::jsArrayToJavaArray (v8::Handle<v8::Array>::Cast (jsValue));
	}
	else if (jsValue->IsObject())
	{
		/*
		// check for proxy type here?
		if (is proxy)
		{

		}
		else // use the KrollV8Dict
		{

		}
		*/
	}
}


// converts java object to js value and recursively converts sub objects if this
// object is a container type
v8::Handle<v8::Value> TypeConverter::javaObjectToJsValue (jobject javaObject)
{
	JNIEnv *env = JNIUtil::getJNIEnv();
	if (env == NULL)
	{
		return v8::Handle<v8::Object>();
	}

	jclass javaObjectClass = env->GetObjectClass (javaObject);
	
	if (env->IsInstanceOf (javaObjectClass, JNIUtil::numberClass))
	{
		jdouble javaDouble = env->CallDoubleMethod (javaObject, JNIUtil::numberDoubleValueMethod);
		return v8::Number::New ((double) javaDouble);
	}
	else if (env->IsInstanceOf (javaObject, JNIUtil::stringClass))
	{
		return v8::String::New ( env->GetStringChars ((jstring) javaObject, 0));
	}
	else if (env->IsInstanceOf (javaObjectClass, JNIUtil::dateClass))
	{
		
	}
	else if (env->IsInstanceOf (javaObjectClass, JNIUtil::hashMapClass))
	{
		v8::Handle<v8::Object> jsObject = v8::Object::New();

		jobject hashMapSet = env->CallObjectMethod (javaObject, JNIUtil::hashMapKeySetMethod);

		jobjectArray hashMapKeys = (jobjectArray) env->CallObjectMethod (hashMapSet, JNIUtil::setToArrayMethod);
		int hashMapKeysLength = env->GetArrayLength (hashMapKeys);

		for (int i = 0; i < hashMapKeysLength; i++)
		{
			jobject javaPairKey = env->GetObjectArrayElement (hashMapKeys, i);
			v8::Handle<v8::Value> v8PairKey = TypeConverter::javaObjectToJsValue (javaPairKey);

			if (v8PairKey->IsNull())
			{
				jobject javaPairValue = env->CallObjectMethod (javaObject, JNIUtil::hashMapGetMethod, javaPairKey);
				jsObject->Set (v8PairKey, TypeConverter::javaObjectToJsValue (javaPairValue));
			}
		}

		return jsObject;
	}
	else if (env->IsInstanceOf (javaObjectClass, JNIUtil::krollProxyClass))
	{
		v8::Handle<v8::Object> jsObject = v8::Object::New();
	}
}


/****************************** private methods ******************************/

// used mainly by the array conversion methods when converting java numeric types 
// arrays to to the generic js number type 
v8::Handle<v8::Array> TypeConverter::javaDoubleArrayToJsNumberArray (jdoubleArray javaDoubleArray)
{
	JNIEnv *env = JNIUtil::getJNIEnv();
	if (env == NULL)
	{
		return v8::Handle<v8::Array>();
	}

	int arrayLength = env->GetArrayLength (javaDoubleArray);
	v8::Handle<v8::Array> jsArray = v8::Array::New (arrayLength);

	jdouble *arrayElements = env->GetDoubleArrayElements (javaDoubleArray, 0);
	for (int i = 0; i < arrayLength; i++)
	{
		jsArray->Set ((uint32_t)i, v8::Number::New (arrayElements [i]));
	}

	return jsArray;
}
