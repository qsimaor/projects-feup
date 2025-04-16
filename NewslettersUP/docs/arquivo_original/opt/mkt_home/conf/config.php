<?php

//----------------------------------------------------------------------
unset($CFG);
global $CFG;
$CFG = new stdClass();
//----------------------------------------------------------------------
$CFG->host = 'mkt.up.pt';
$CFG->webroot = '/timeline';
$CFG->weburl = 'https://'.$CFG->host.$CFG->webroot;
$CFG->mautic = 'https://mkt.up.pt/';

$CFG->home = '/opt/mkt_home';
$CFG->docroot = '/var/www/html/timeline';
$CFG->libroot = '/opt/mkt_home/lib';

$CFG->logfile = $CFG->home . '/logs/timeline.log';
$CFG->banfile = $CFG->home . '/logs/ban.log';
//----------------------------------------------------------------------
// JSON's repository
$CFG->jsons = $CFG->home . '/data/jsons';

$CFG->instancias = array('alumni','cdup','cefup','cultura','divulgacao','eugloh','icbas','inovped','ispup','fadeup','faup','fbaup','fcnaup','fcup','fdup','fep','feup','ffup','flup','fmdup','fmup','fpce','reitoria','sipreitoria','updigital','upin');

$CFG->datas = array('2019','2020','2021','2022','2023','2024');

$CFG->categories = array(
        "alumni"=>array(5),
        "fpce"=>array(6,8,12),
        "feup"=>array(11,12,16,18,21),
        "fcup"=>array(1),
	"faup"=>array(1,3,4),
	"fcnaup"=>array(7),
	"fmup"=>array(4),
	"fmdup"=>array(3),
	"flup"=>array(38,47,56,57),
        "fep"=>array(5,19),
        "cultura"=>array(2),
        "reitoria"=>array(13),
	"icbas"=>array(11),
        "sipreitoria"=>array(16),
        "reitoria"=>array(13),
        "flup"=>array(38,47,56,57),
	"ispup"=>array(3),
	"updigital"=>array(42)
);

$CFG->publications = array(
        "cultura"=>array( "newsletter"),
        "feup"   =>array( "highlights","feupworld","communityofchange","feupworld2023","feup-dna"),
        "alumni" =>array( "newsletter"),
        "faup" =>array( "newsletter"),
        "cefup" =>array( "newsletter"),
        "divulgacao" =>array( "newsletter"),
        "fcup" =>array( "noticias-fcup"),
	"fmdup" =>array( "newsletter"),
	"fmup" =>array( "newsletter-fmup"),
	"fmdup" =>array( "newsletter"),
	"fep" =>array( "newsletter","newsletters"),
        "fpce" =>array( "newsletter-fpceup","newsletter-cpup","newsletter-sec"),
	"reitoria" =>array( "sip"),
	"fcnaup" =>array("newsletter"),
        "faup" => array( "newsletter", "emailing"),
	"icbas" => array( "newsletter"),
        "sipreitoria" => array ("timeline"),
        "flup" => array("uec-newsletter","uec-formacao-professores","newsletter-flup","esta-semana-na-flup"),
	"ispup" => array("newsletter"),
	"updigital" => array("newsletter")
);
//"fpce" =>array( "newsletter-fpceup", "newsletter-cpup", "newsletter-sec"),
$CFG->pubcat = (object) array(
        'alumni-newsletter'=>5,
        'cultura-newsletters'=>2,
        'feup-highlights'=>11,
	'feup-feupworld'=>12,
	'feup-communityofchange'=>16,
	'feup-feupworld2023'=>18,
	'feup-dna'=>21,
        'fpce-newsletter-fpceup'=>6,
	'fpce-newsletter-cpup'=>8,
	'fpce-newsletter-sec'=>12,
        'faup-newsletter'=>1,
        'faup-emailing'=>3,
        'faup-convites'=>4,
	'fcup-noticias-fcup'=>1,
	'fep-newsletters'=>5,
	'fep-newsletter'=>19,
	'fcnaup-newsletter'=>7,
	'icbas-newsletter'=>11,
        'sipreitoria-timeline'=>16,
        'reitoria-sip'=>13,
	'flup-uec-newsletter'=>38,
	'esta-semana-na-flup'=>57,
	'newsletter-flup'=>47,
	'flup-uec-formacao-professores'=>56,
	'ispup-newsletter'=>3,
	'fmup-newsletter-fmup'=>4,
	'updigital-newsletter'=>42
);
//'fpce-newsletter-cpup'=>8
//'fpce-newsletter-sec'=>12,
//----------------------------------------------------------------------
// tr -c -d '0123456789abcdefghijklmnopqrstuvwxyz' </dev/urandom | dd bs=32 count=1 2>/dev/null;echo
$CFG->secretsalt='56lb8mslb44ghln2a0cmlnpl5s74ug3k';

// NEVER FOR PRODUCTION SERVER!!!
$CFG->DEBUG=false;
$CFG->WIP=false; // Work in Progress
//----------------------------------------------------------------------
// to avoid direct document access
define('GEEKTOTHEBONE', 1);

//----------------------------------------------------------------------
// Don't need to change anything bellow this line!
//
require($CFG->libroot . '/lib.php');

// Web Application Firewall
require($CFG->libroot . '/xwaf.php'); // Before all your code starts.
$xWAF = new xWAF();
$xWAF->start();
// Done, Protection enabled.
//----------------------------------------------------------------------
