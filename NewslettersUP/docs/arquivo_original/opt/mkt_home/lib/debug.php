<?php

defined('GEEKTOTHEBONE') || die();

//----------------------------------------------------------------------
if($CFG->DEBUG){
        ini_set('display_errors', 'On');
        error_reporting(E_ALL);
//      error_reporting(E_ALL | E_STRICT);
//      error_reporting(E_ALL ^ E_STRICT);

}
function debugging_system() {
        global $CFG, $USER, $_SESSION;
//        if($CFG->DEBUG && user_is_administrator() && error_get_last() != NULL){
        if($CFG->DEBUG && error_get_last() != NULL){
                var_dump(error_get_last());
        }
}
function debug( $var, $title="" ) {
        global $CFG;
        if($CFG->DEBUG && user_is_administrator()){
                print "<pre>";
                ?>
                <h3>Debug( <?=$title?> )</h3>
                <?php
                print_r($var);
                print "</pre>";
                ?>
                <?php
        }
}
//----------------------------------------------------------------------
// There is no php closing tag in this file,
// it is intentional because it prevents trailing whitespace problems!
