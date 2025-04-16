<?php
header("HTTP/1.1 418 Teatime");

require_once(__DIR__.'/../loader.php');
html_headers();

//start_security();
writeToLog("*** MOUSE_TRAP ***",1);
writeToBanFile();
//safeRedirect("/");
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
		<link rel="stylesheet" href="<?=$CFG->webroot?>/assets/css/418.css">
        </head>
	<body>
                <div class="container-fluid">
                        <div class="row">
                                <div class="col-md-6 offset-md-3 col-xs-12">
                                        <p>&nbsp;</p>
                                        <p>&nbsp;</p>
                                        <h1><span class="white">http 418.</span><br>I'm a Teapot.</h1>
                                        <p><small>(<a href="https://tools.ietf.org/html/rfc2324">RFC2324</a>, <a href="https://tools.ietf.org/html/rfc7168">RFC7168</a>)</small></p>
                                <p>&nbsp;</p>
                                        <img class="center-block faa-tada animated" src="<?=$CFG->weburl?>/assets/images/teapot.png"">
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
                                  echo " it's TEA TIME.</p>";
                                ?>
                        </div>
                </div>
        </body>
</html>
