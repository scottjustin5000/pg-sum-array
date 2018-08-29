# pg-sum-array
> postgres extension to sum the values of an array


### Install
```
make install && make installcheck
```

### Usage
```sql
CREATE EXTENSION sum_array
SELECT sum_array('{1,2,3,4,5}'::int[]); //outputs 15
SELECT sum_array('{1.1,2.2,3.3,4.4,5.5}'::float[]); //outputs 16.5
```
