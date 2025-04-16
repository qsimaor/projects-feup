<?php
//require_once("../conf/config.php");
defined('GEEKTOTHEBONE') || die();

//writeToLog("*** 404 ***",1);

function start_security(){
        //------------------------------------------------------------------
        /* prevent XSS. */
        $_GET   = filter_input_array(INPUT_GET, FILTER_SANITIZE_STRING);
        $_POST  = filter_input_array(INPUT_POST, FILTER_SANITIZE_STRING);
}
function writeToBanFile($event="") {
        global $CFG, $_SESSION;
                try {
                        if(!file_exists($CFG->banfile)) {
                                $log="#<?php die('Forbidden.'); ?>\n";
                                $log .= "#[<remote_address>][<timestamp>][<userid>][<host>][<referer>][<event>]\n";
                        } else {
                                $log="";
                        }
                        //date_default_timezone_set($CFG->timezone);
                        $time = date('d/m/Y_H:i:s', time());
                        $ip = $_SERVER["REMOTE_ADDR"]; // Get the IP from superglobal
                        $host = gethostbyaddr($ip);
                        $request = $_SERVER['REQUEST_SCHEME']."://".$_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI'];
                        if(isset($_SERVER['HTTP_REFERER'])){
                                $referer = $_SERVER['HTTP_REFERER'];
                        } else {
                                $referer = "";
                        }
                        if(isset($_SERVER['UPortoNMec']) && ($_SERVER['UPortoNMec']!==NULL)){
                                $s=$_SERVER['UPortoNMec'];
                        } else {
                                $s="";
                        }
                        $log .= "[".$ip."] [".$time."] [".$s."] [".$host."] [".$referer."] [".$event."]\n";
                        file_put_contents($CFG->banfile, $log, FILE_APPEND | LOCK_EX);
                } catch (Exception $err) {
                        if($CFG->DEBUG) print_r($err->getMessage());
                }
}
function writeToLog($event,$hack=0) {
        global $CFG, $_SESSION;
                try {
                        if(!file_exists($CFG->logfile)) {
                                $log="#<?php die('Forbidden.'); ?>\n";
                                $log .= "#[<timestamp>][<event>][<request>][<userid>][<remote_address>][<host>][<referer>]\n";
                        } else {
                                $log="";
                        }
                        //date_default_timezone_set($CFG->timezone);
                        $time = date('d/m/Y_H:i:s', time());

                        if(!isset($_SERVER["REMOTE_ADDR"]) || $_SERVER["REMOTE_ADDR"]===""){
                                $ip="127.0.0.1";
                        } else {
                                $ip = $_SERVER["REMOTE_ADDR"]; // Get the IP from superglobal
			}
                        $host = gethostbyaddr($ip);
                        if(!isset($_SERVER['SERVER_NAME']) || $_SERVER['SERVER_NAME']==="") {
                                $servername="localhost";
                        } else {
                                $servername=$_SERVER['SERVER_NAME'];
                        }
                        if(!isset($_SERVER['REQUEST_SCHEME']) || $_SERVER['REQUEST_SCHEME']==="") {
                                $request_uri="";
                        } else {
                                $request_uri=$_SERVER['REQUEST_URI'];
                        }
                        if(!isset($_SERVER['REQUEST_SCHEME']) || $_SERVER['REQUEST_SCHEME']==="") {
                                $request="cli";
                        } else {
                                $request = $_SERVER['REQUEST_SCHEME']."://".$servername.$request_uri;
                        }
                        if(isset($_SERVER['HTTP_REFERER'])){
                                $referer = $_SERVER['HTTP_REFERER'];
                        } else {
                                $referer = "";
                        }
                        if(isset($_SERVER['UPortoNMec']) && ($_SERVER['UPortoNMec']!==NULL)){
                                $s=$_SERVER['UPortoNMec'];
                        } else {
                                $s="";
                        }
                        if($CFG->DEBUG || $hack) {
                                $log .= "[".$time."] [".$event."] [".$request."] [".$s."] [".$ip."] [".$host."] [".$referer."]\n";
                        } else {
                                $log .= "[".$time."] [".$event."] [ ] [".$s."] [".$ip."] [".$host."] [ ]\n";
                        }
                        file_put_contents($CFG->logfile, $log, FILE_APPEND | LOCK_EX);
                } catch (Exception $err) {
                        if($CFG->DEBUG) print_r($err->getMessage());
                }
}
function html_headers($nocache=1,$click=1,$xss=1,$nosniff=1) {
        if($nocache){
                // No-cache
                header('Expires: Tue, 01 Jan 2000 00:00:00 GMT');
                header('Last-Modified: ' . gmdate('D, d M Y H:i:s') . ' GMT');
                header('Cache-Control: no-store, no-cache, must-revalidate, max-age=0');
                header('Cache-Control: post-check=0, pre-check=0', false);
                header('Pragma: no-cache');
        }
        if($click){
                // Security: Clickjacking
                header('X-Frame-Options: DENY');
        }
        if($xss){
                // Security: XSS-Protection
                header('X-XSS-Protection: 1; mode=block');
                header("Feature-Policy: geolocation 'none'; microphone 'none'; payment 'none';");
        }
        if($nosniff){
                // Security: inform browsers that they should not do MIME type sniffing
                header('X-Content-Type-Options: nosniff');
                header('X-Download-Options: noopen ');
                header('Referrer-Policy: same-origin');
        }
}
function generateFormToken($form) {

       // generate a token from an unique value
        $token = md5(uniqid(microtime(), true));

        // Write the generated token to the session variable to check it
        // against the hidden field when the form is sent
        $_SESSION[$form.'_token'] = $token;

        return $token;

}
function verifyFormToken($form) {

    // check if a session is started and a token is transmitted, if not return an error
        if(isset($_SESSION[$form.'_token']) !== true) {
                return false;
    }

        // check if the form is sent with token in it
        if(isset($_POST['token'])  !== true) {
                return false;
    }

        // compare the tokens against each other if they are still the same
        if ($_SESSION[$form.'_token'] !== $_POST['token']) {
                return false;
    }

        return true;
}
