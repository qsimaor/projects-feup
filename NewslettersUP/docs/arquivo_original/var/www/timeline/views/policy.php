<?php

require_once(__DIR__.'/../loader.php');

html_headers();

start_security();
writeToLog("views/policy.php",0);
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
<!--  <link href="<?=$CFG->webroot?>/assets/css/timelines.css" rel="stylesheet">
-->
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
	
				<h1>Privacy Policy</h1>

<p>This privacy policy has been compiled to better serve those who are 
concerned with how their 'Personally Identifiable Information' (PII) is 
being used online. PII is information that can be used on its own or with other 
information to identify, contact, or locate a single person, or to identify an individual in context. Please read our privacy policy carefully to get a clear understanding of how we collect, use, protect or otherwise handle your Personally Identifiable Information in accordance with our website.</p>
<h2>What personal information do we collect from the people that visit our website or app?</h2>
<p>We don't collect any personal information on this site.</p>

<H2>When do we collect information?</H2>

<P>We only collect information about your IP address for log purposes.</P>

<H2>How do we use your information?</H2>

<p>We may use the information we collect from you when you surf the website:</p>
<ul>
<li>To improve our website in order to better serve you;</li>
<li>To allow us to better service you in responding to your customer service requests.</li>
</ul>

<H2>How do we protect your information?</H2>

<p>By not having or storing any sensitive information from you.</p>

<p>In addition, all sensitive information you supply is encrypted via Secure Socket Layer (SSL) technology.</p>

<H2>Do we use 'cookies'?</H2>
<p>Yes. Cookies are small files that a site or its service provider 
transfers to your computer's hard drive through your Web browser (if 
you allow) that enables the site's or service provider's systems to 
recognize your browser and capture and remember certain information. 
For instance, we use cookies to help us remember your language settings. We also use cookies to help us compile aggregate data about site traffic and site interaction so that we can offer better site experiences and tools in the future.</p>

<p>We use cookies to Understand and save user's preferences for future visits.</p>

<p>You can choose to have your computer warn you each time a cookie is being sent, or you can choose to turn off all cookies. You do this through your browser settings. Since browser is a little different, look at your browser's Help Menu to learn the correct way to modify your cookies.</p>

<p>If you turn cookies off, some features will be disabled. It won't 
affect the user's experience that make your site experience more efficient and may not function properly.</p>

<H2>Third-party disclosure</H2>
<p>We do not sell, trade, or otherwise transfer to outside parties your Personally Identifiable Information.</p>

<H3>Third-party links</H3>

<p>We do not include or offer third-party products or services on our website.</p>

<p>Last Edited on Nov the 21<sup>th</sup>, 2022.</p>

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

