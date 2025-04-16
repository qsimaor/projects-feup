<?php

//require_once("{$_SERVER['DOCUMENT_ROOT']}/timeline/router.php");
//require_once(dirname(__FILE__)."/../conf/config.php");
require_once(dirname(__FILE__)."/router.php");
// ##################################################
// ##################################################
// ##################################################
// Static GET
// In the URL -> http://localhost
// The output -> Index
//get('/', 'index.php');
get($CFG->webroot, 'index.php');
get($CFG->webroot.'/acerca', 'views/xpto.php');
//get($CFG->webroot.'/x', 'views/novo404.php');
get($CFG->webroot.'/about', 'views/about.php');
get($CFG->webroot.'/policy', 'views/policy.php');
get($CFG->webroot.'/conditions', 'views/conditions.php');
get($CFG->webroot.'/418', 'views/teatime.php');
// Dynamic GET. Example with 1 variable
// The $id will be available in user.php
//get('/user/$id', 'user.php');
get($CFG->webroot.'/$uo/$publication', 'timeline.php');

// Dynamic GET. Example with 2 variables
// The $name will be available in user.php
// The $last_name will be available in user.php
//get('/user/$name/$last_name', 'user.php');

// Dynamic GET. Example with 2 variables with static
// In the URL -> http://localhost/product/shoes/color/blue
// The $type will be available in product.php
// The $color will be available in product.php
//get('/product/$type/color/:color', 'product.php');

// Dynamic GET. Example with 1 variable and 1 query string
// In the URL -> http://localhost/item/car?price=10
// The $name will be available in items.php which is inside the views folder
//get('/item/$name', 'views/items.php');


// ##################################################
// ##################################################
// ##################################################
// any can be used for GETs or POSTs

// For GET or POST
// The 404.php which is inside the views folder will be called
// The 404.php has access to $_GET and $_POST
any('/404','views/novo404.php');
//any('/404','views/x.php');
//any('/error','views/teatime.php');
