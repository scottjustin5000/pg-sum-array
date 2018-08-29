-- complain if script is sourced in psql, rather than via CREATE EXTENSION
\echo Use "CREATE EXTENSION sum_array" to load this file. \quit
CREATE OR REPLACE FUNCTION sum_array(anyarray) RETURNS DOUBLE PRECISION
AS 'sum_array', 'sum_array'
LANGUAGE C IMMUTABLE STRICT;