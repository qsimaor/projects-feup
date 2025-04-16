<?php
require_once('/opt/mkt_home/conf/config.php');
require_once($CFG->libroot.'/security.php');

header("HTTP/1.0 404 Not Found");
html_headers();

start_security();
writeToLog("*** 404 ***",1);
?>
<!DOCTYPE html>

<html>
	<head>
		<meta name="viewport" content="width=device-width, initial-scale=1.0">
		<meta name="description" content="">
		<meta name="author" content="246033">
                <!-- Le styles -->
		<link href="<?=$CFG->webroot?>/assets/vendor/bootstrap/css/bootstrap.min.css" rel="stylesheet">               
		<script src="<?=$CFG->webroot?>/assets/js/jquery-3.3.1.min.js"></script>
		<script src="<?=$CFG->webroot?>/assets/js/bootstrap-4.1.1/js/bootstrap.js"></script>
		<!-- Fontawesome -->
		<script defer src="<?=$CFG->webroot?>/assets/js/fontawesome-all.js"></script>
		<link rel="stylesheet" href="<?=$CFG->webroot?>/assets/css/font-awesome-animation.min.css">
		<link rel="stylesheet" href="<?=$CFG->webroot?>/assets/css/novo404.css">
        </head>
	<body>
		<p>&nbsp;</p>
                <div class="container-fluid">
                        <div class="row">
				<div class="col-md-8 offset-md-2 d-flex justify-content-center">
					<h1>ERROR 404</h1>
				</div>
			</div>
                        <div class="row">
				<div class="col-md-8 offset-md-2">
					<img class="center-block faa-float animated" src="<?=$CFG->webroot?>/assets/images/error-404.png">
				</div>
			</div>
                        <div class="row">
                                <div class="col-md-8 offset-md-2 d-flex justify-content-center">
				<p>page is not found.</p>
                               </div>
			</div>
                        <div class="row">
                                <div class="col-md-8 offset-md-2 d-flex justify-content-center">
				<p>the page doesn't exist or was deleted</p>
				</div>
			</div>
                </div>
        </body>
</html>
