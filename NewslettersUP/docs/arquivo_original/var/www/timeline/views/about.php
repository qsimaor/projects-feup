<?php

require_once(__DIR__.'/../loader.php');

html_headers();

start_security();
writeToLog("views/about.php",0);
?>
<!DOCTYPE html>
<html lang="pt" style="scroll-behavior: smooth;">
<head>
    <meta charset="utf-8">
    <meta http-equiv="x-ua-compatible" content="ie=edge">
    <title>TIMELINE</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta name="description" content="">
    <meta name="author" content="Universidade do Porto">

    <link rel="icon" href="<?=$CFG->webroot?>/static/images/favicons/favicon.ico">

<!-- -->
  <!-- Google Fonts -->
<link rel="preconnect" href="https://fonts.googleapis.com">
<link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
<link href="https://fonts.googleapis.com/css2?family=Lato:wght@300;900&family=Roboto:wght@100;400&display=swap" rel="stylesheet">

  <!-- Vendor CSS Files -->
  <link href="<?=$CFG->webroot?>/assets/vendor/aos/aos.css" rel="stylesheet">
  <link href="<?=$CFG->webroot?>/assets/vendor/bootstrap/css/bootstrap.min.css" rel="stylesheet">
  <!-- <link href="/timeline/assets/vendor/bootstrap-icons/bootstrap-icons.css" rel="stylesheet"> -->
  <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap-icons@1.3.0/font/bootstrap-icons.css">
  <!-- <link href="/timeline/assets/vendor/boxicons/css/boxicons.min.css" rel="stylesheet"> -->
  <link href='https://unpkg.com/boxicons@2.1.4/css/boxicons.min.css' rel='stylesheet'>
  <link href="<?=$CFG->webroot?>/assets/vendor/glightbox/css/glightbox.min.css" rel="stylesheet">
  <link href="<?=$CFG->webroot?>/assets/vendor/swiper/swiper-bundle.min.css" rel="stylesheet">

  <!-- Template Main CSS File -->
  <link href="<?=$CFG->webroot?>/assets/css/style.css" rel="stylesheet">
  <link href="<?=$CFG->webroot?>/assets/css/updigital.css" rel="stylesheet">
  <link href="/s/css/album.css" rel="stylesheet">
  <link href="<?=$CFG->webroot?>/assets/css/timelines.css" rel="stylesheet">

</head>
<body>
<header id="header" class="fixed-top">
  <div class="container-fluid d-flex justify-content-between align-items-center">
  <!-- ======= Header ======= -->
<!-- -->
</div>
<div class="row header-title">
<div class="d-flex flex-row justiqfy-content-between">
<div class="col-8 offset-1">
  <h1>ARQUIVO DE NEWSLETTERS | U.PORTO</h1>
</div>
<div class="col-2">
        <a href="<?=$CFG->webroot?>/" aria-hidden="false"><img src="<?=$CFG->webroot?>/assets/images/logo_updigital_h_white.png" alt="" class="img-fluid d-none d-md-block"></a>
        <a href="<?=$CFG->webroot?>/" aria-hidden="false"><img src="<?=$CFG->webroot?>/assets/images/logo_updigital_s_white.png" alt="" class="img-fluid d-md-none d-lg-none d-xl-none"></a>
</div>
</div>
<!-- -->

</header>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<style>
.btn{
	color: #666;
}
</style>
<div class="container-fluid content">
<div class="row" id="ementa">
  <div class="col offset-1">
<!-- cards (start) -->
	<h1>Acerca</h1>
	<p>Esta ferramenta pretende ser uma montra das newsletters e demais comunicações efetuadas através das instâncias do Mautic em mkt.up.pt.</p>
	<h2>Equipa de desenvolvimento</h2>
	<ul>
		<li>Rodolfo Matos - Concepção e programação<br>
		&nbsp;&nbsp;(... após muita insistência de Mafalda Leite (FEUP) <i class="bi bi-emoji-smile"></i> );</li>
		<li>Modelo de site UPdigital por Vítor Carvalho e Carla Amaral;</li>
		<li>Sugestões de alteração ao Modelo do site por Marta Ferreirinha (FEP).</li>
	</ul>
	<h2>Equipa de Administração de Sistemas</h2>
	<p>Rodolfo Matos, Jorge Cunha, Pedro Graça</p>
	<h2>Agradecimentos</h2>
	<p>Ricardo Faria e Ana Duarte (FEP)</p>
	<h2>Third party disclaimer</h2>
	<ul>
		<li>Kelly - Bootstrap CV Resume HTML Template - © Copyright Kelly. All Rights Reserved<br>Designed by <a href="https://bootstrapmade.com/">BootstrapMade</a></li>
		<li>Code licensed under <a href="http://www.apache.org/licenses/LICENSE-2.0" target="_blank">Apache License v2.0</a>, documentation under <a href="http://creativecommons.org/licenses/by/3.0/">CC BY 3.0</a>;</li>
		<li>jQuery is provided under the <a href="https://jquery.org/license/">MIT license</a>;</li>
		<li>Bootstrap is provided under the <a href="https://github.com/twbs/bootstrap/blob/master/LICENSE">MIT license</a>;</li>
		<li>Fontawesome is provided under the <a href="https://github.com/twbs/bootstrap/blob/master/LICENSE">MIT license</a> (code) and <a href="http://scripts.sil.org/OFL">SIL OFL 1.1</a> (font);</li>
		<li>PHP is copyright by the <a href="https://php.net/credits.php">PHP Group</a>.</li>
		<li>Python is <a href="https://www.python.org/doc/copyright/">Open Source</a>.</li>
	</ul>
	

<!-- cards (end) -->
  </div>
</div>
</div>
  <footer id="footer">

<!-- ======= Footer ======= -->
<?=include_footer();?>
<!-- End  Footer -->

  <div id="preloader"></div>
  <a href="#" class="back-to-top d-flex align-items-center justify-content-center"><i class="bi bi-arrow-up-short"></i></a>

  <!-- Vendor JS Files -->
  <script src="<?=$CFG->webroot?>/assets/vendor/purecounter/purecounter_vanilla.js"></script>
  <script src="<?=$CFG->webroot?>/assets/vendor/aos/aos.js"></script>
  <script src="<?=$CFG->webroot?>/assets/vendor/bootstrap/js/bootstrap.bundle.min.js"></script>
  <script src="<?=$CFG->webroot?>/assets/vendor/glightbox/js/glightbox.min.js"></script>
  <script src="<?=$CFG->webroot?>/assets/vendor/isotope-layout/isotope.pkgd.min.js"></script>
  <script src="<?=$CFG->webroot?>/assets/vendor/swiper/swiper-bundle.min.js"></script>
  <script src="<?=$CFG->webroot?>/assets/vendor/waypoints/noframework.waypoints.js"></script>
  
  <!-- Template Main JS File -->
  <script src="<?=$CFG->webroot?>/assets/js/main.js"></script>

</body>

</html>

