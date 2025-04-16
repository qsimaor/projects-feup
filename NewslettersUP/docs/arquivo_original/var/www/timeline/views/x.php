<pre>
<?php
var_dump($_GET);
var_dump($_POST);
//require_once('/opt/mkt_home/conf/config.php');
require_once(__DIR__.'/../loader.php');
//require_once($CFG->libroot.'/security.php');

function myrow($id, $data)
{
    return "<tr><th>$id</th><td>$data</td></tr>\n";
}

$arr = get_defined_functions();

print_r($arr['user']);
?>
