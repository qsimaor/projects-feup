<?php

//defined('GEEKTOTHEBONE') || die();

require_once('/opt/mkt_home/conf/config.php');
//global $CFG;
//----------------------------------------------------------------------

$CFG->version='<div class="nowrap">Version 0.0.1 (build 1)</div>';

//----------------------------------------------------------------------
require_once($CFG->libroot.'/debug.php');
require_once($CFG->libroot.'/lib2.php');
require_once($CFG->libroot.'/security.php');
require_once($CFG->libroot.'/router.php');
require_once($CFG->libroot.'/routes.php');


//var_dump($CFG);
//exit;
//----------------------------------------------------------------------
// There is no php closing tag in this file,
// it is intentional because it prevents trailing whitespace problems!
