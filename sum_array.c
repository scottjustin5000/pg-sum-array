#include "postgres.h"
#include "fmgr.h"
#include "utils/builtins.h"
#include "catalog/pg_type.h"
#include "utils/array.h"

PG_MODULE_MAGIC;

Datum sum_array(PG_FUNCTION_ARGS);
PG_FUNCTION_INFO_V1(sum_array);

Datum 
sum_array(PG_FUNCTION_ARGS) {
  ArrayType *array;
  array = PG_GETARG_ARRAYTYPE_P(0);
  Oid valueType;
  valueType = ARR_ELEMTYPE(array);

   if (valueType != INT2OID &&
      valueType != INT4OID &&
      valueType != INT8OID &&
      valueType != FLOAT4OID &&
      valueType != FLOAT8OID) {
    ereport(ERROR, (errmsg("sum_array only works with numeric value types")));
  }
  
  int16 valueTypeWidth;
  // should always be true 
  bool valueTypeByValue;
  char valueTypeAlignmentCode;
  Datum *arrayContent;

  // List of "is null" flags for the array contents:
  bool *arrayNullFlags;
  int arrayLength;
  float8* array2;

  // The size of array:
  arrayLength = (ARR_DIMS(array))[0];

  get_typlenbyvalalign(valueType, &valueTypeWidth, &valueTypeByValue, &valueTypeAlignmentCode);
  deconstruct_array(array, valueType, valueTypeWidth, valueTypeByValue, valueTypeAlignmentCode, &arrayContent, &arrayNullFlags, &arrayLength);
  array2 = palloc0(sizeof(float8) * arrayLength);
  int i = 0;
  switch (valueType) {
    case INT2OID:
      for (i = 0; i < arrayLength; i++) {
        array2[i] = DatumGetInt16(arrayContent[i]);
      }
      break;
    case INT4OID:
      for (i = 0; i < arrayLength; i++) {
        array2[i] = DatumGetInt32(arrayContent[i]);
      }
      break;
    case INT8OID:
      for (i = 0; i < arrayLength; i++) {
        array2[i] = DatumGetInt64(arrayContent[i]);
      }
      break;
    case FLOAT4OID:
      for (i = 0; i < arrayLength; i++) {
        array2[i] = DatumGetFloat4(arrayContent[i]);
      }
      break;
    case FLOAT8OID:
      for (i = 0; i < arrayLength; i++) {
        array2[i] = DatumGetFloat8(arrayContent[i]);
      }
      break;
  }
  float8 sum = 0.0;

  for (int i = 0; i < arrayLength; i++){
   sum += array2[i];
  }
   PG_RETURN_FLOAT8(sum);
}