CREATE EXTENSION sum_array;
SELECT sum_array('{1,3,6,7,9,3}'::int[]);
SELECT sum_array('{6.4,3.5,8.8,5.0,1.0}'::float[]);