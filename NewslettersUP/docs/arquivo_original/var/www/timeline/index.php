<?php

require_once('loader.php');

html_headers();

start_security();
writeToLog("index.php",0);
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
<!-- Search (start) -->
		<div class="row">
			<div class="col-md-10 offset-1"> 
				<div class="input-group mb-3">
				  <div class="input-group-prepend">
					<span class="input-group-text" id="basic-addon1"><i class="bi bi-search"></i></span>
				  </div>
				<input type="text" id="mySearch" onkeyup="mySearchFunction()" placeholder="Procurar...">
				</div>			
			</div> 
		</div>
                <div class="row">
                        <div class="col-md-10 offset-md-1">
<!-- Search (end) -->
<div class="row" id="ementa">
<!-- cards (start) -->
<?php
foreach(list_uos() as $uo){
	index_card($uo);
}
?>
<!-- cards (end) -->
                        </div>
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

	<script>
		function mySearchFunction() {
		  // Declare variables
		  var input, filter, ementa, card, i;
		  input = document.getElementById('mySearch');
		  filter = input.value.toUpperCase();
		  ementa = document.getElementById('ementa');
		  card = ementa.getElementsByClassName('card');

		  // Loop through all list items, and hide those who don't match the search query
		  for (i = 0; i < card.length; i++) {
			  name = card[i].getAttribute("name");
			  if (name.toUpperCase().indexOf(filter) > -1) {
				//card[i].style.display = "";
				card[i].closest(".col-md-3").style.display = "";
			} else {
				//card[i].style.display = "none";
				card[i].closest(".col-md-3").style.display = "none";
			}
		  }
		}
	</script>
</body>

</html>

