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
		<link rel="stylesheet" href="<?=$CFG->webroot?>/assets/css/404.css">
        </head>
	<body>
		<p>&nbsp;</p>
                <div class="container-fluid">
                        <div class="row">
                                <div class="col-md-6">
					<img class="center-block faa-float animated" src="<?=$CFG->webroot?>/assets/images/404.png">
                                <p>&nbsp;</p>
				</div>
			</div>
			<div class="row">
				<div class="offset-md-6 col-md-6">
                                        <h1><span class="gray">http 404.</span><br>Page not found.</h1>
                                <p>&nbsp;</p>
                                <?php
                                /*
                                  // 20 seconds delay to load page... ;)
                                  ob_start(); // not needed if output_buffering is on in php.ini
                                  ob_implicit_flush(); // implicitly calls flush() after every ob_flush()
                                  ob_end_flush();
                                  echo "<p>The requested URL cannot provide coffee<br>because";

                                  for ($i = 0; $i < 20; $i++)
                                  {
                                        echo ".";
                                        @ob_flush();
                                        sleep(1);
                                  }
                                  */
echo " try something else...</p>";
//debugging_system();
                                ?>
                        </div>
                </div>
        </body>
</html>
