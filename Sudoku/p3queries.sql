/* excercise 1 */

/* 1a. */

select relname, relkind from pg_class where relname like 'customers%';

/* 1b. */

select relname, reltuples, relpages from pg_class where relpages > 7;

/* 1c. */

select tablename, attname, n_distinct from pg_stats where tablename = 'customers';

/* 1d. */

select count(distinct email), count(distinct customerid), count(distinct country),count(distinct password),count(distinct income),count(distinct firstname),count(distinct lastname),count(distinct address1),count(distinct address2),count(distinct city),count(distinct state), count(distinct zip),count(distinct region), count(distinct phone),count(distinct creditcardtype),count(distinct creditcard),count(distinct creditcardexpiration),count(distinct username),count(distinct age),count(distinct gender) from customers; 


/* excercise 3 */

\i setup_db.sql
VACUUM;
ANALYZE;

CREATE INDEX customers_country ON customers(country);
VACUUM;
ANALYZE;

/* 3a. */
select relpages from pg_class where relname = 'customers_country';

/* 3b. */

explain select * from customers where country = 'Japan';

CLUSTER customers_country ON customers;
VACUUM;
ANALYZE;

/* 3d. */

explain select * from customers where country = 'Japan';


/* excercise 5 */
\i setup_db.sql
VACUUM;
ANALYZE;

/* 5a. */

explain select avg(totalamount) as avgOrder, country from Customers C, Orders O where C.customerid = O.customerid group by country order by avgOrder;

set enable_hashjoin = false;

explain select avg(totalamount) as avgOrder, country from Customers C, Orders O where C.customerid = O.customerid group by country order by avgOrder;

/* 5b. */

set enable_hashjoin = true;

explain select * from Customers C, Orders O where C.customerid = O.customerid order by C.customerid;

set enable_mergejoin = false;

explain select * from Customers C, Orders O where C.customerid = O.customerid order by C.customerid;

set enable_mergejoin = true;


/* excercise 7 */
\i setup_db.sql
VACUUM;
ANALYZE;

/* 7a. */
explain select customerid, lastname, numorders from (select C.customerid, C.lastname, count(*) as numorders from Customers C, Orders O where C.customerid = O.customerid and C.country = 'Japan' group by C.customerid, lastname) as ordercounts1 where 5>= (select count(*) from ( select C.customerid, C.lastname, count(*) as numorders from Customers C, Orders O where C.customerid = O.customerid and C.country = 'Japan' group by C.customerid, lastname) as ordercounts2 where ordercounts1.numorders < ordercounts2.numorders) order by customerid;

/* 7b. */

create view OrderCountJapan as select c.customerid, count(*) as numorders from Customers c, Orders o where c.customerid = o.customerid and c.country = 'Japan' group by c.customerid;

create view MoreFrequentJapanCustomers as select o.customerid, (select count(*) from ordercountjapan o2 where o.customerid != o2.customerid and o.numorders < o2.numorders group by o.customerid) as oRank from OrderCountJapan o;

/* 7c. */
select m.customerid, c.lastname, o.numorders from MoreFrequentJapanCustomers m, customers c, OrderCountJapan o where m.oRank < 5 and m.customerid = c.customerid and m.customerid = o.customerid order by m.customerid;

/* 7d. */
explain select m.customerid, c.lastname, o.numorders from MoreFrequentJapanCustomers m, customers c, OrderCountJapan o where m.oRank < 5 and m.customerid = c.customerid and m.customerid = o.customerid order by m.customerid;

drop view MoreFrequentJapanCustomers;
drop view OrderCountJapan; 

