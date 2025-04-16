<?php

require_once(__DIR__.'/loader.php');
start_security();
html_headers();
$uo=htmlspecialchars($uo);
$publication=htmlspecialchars($publication);

writeToLog("timeline/".$uo."/".$publication,0);

// IMPORTANT: Variables validation
if(!uo_is_proper($uo)){
	safeRedirect($CFG->webroot."/418");
	exit;
}

if(!publication_is_proper($uo,$publication)){
	safeRedirect($CFG->webroot."/418");
	exit;
}
//writeToLog("timeline.php/".$uo."/".$publication,0);	
?>
<!DOCTYPE html>
<html lang="pt" style="scroll-behavior: smooth;">
<head>
    <meta charset="utf-8">
    <meta http-equiv="x-ua-compatible" content="ie=edge">
    <title><?=strtoupper(htmlspecialchars($uo))?></title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta name="description" content="">
    <meta name="author" content="Universidade do Porto">

 <!--   <link rel="icon" href="<?=$CFG->webroot?>/static/images/favicons/favicon.ico">
-->

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


</head>
<body>

<style>
#header {
        background-color: <?=coloring($uo,$publication,'banner')?>;
}
.portfolio #portfolio-flters li {
	border-radius: 0;
}
.portfolio #portfolio-flters li:hover,
.portfolio #portfolio-flters li.filter-active {
	background: <?=coloring($uo,$publication,'buttons')?>;
}
.portfolio .portfolio-wrap {
	border: 2px solid  <?=coloring($uo,$publication,'frame')?>;
	margin-bottom: 5px;
}
.back-to-top {
	background: <?=coloring($uo,$publication,'buttons')?>;
}
.header-title h1 {
	color: <?=coloring($uo,$publication,'uplogo')?>
}
</style>

<header id="header" class="fixed-top">
  <div class="container-fluid d-flex justify-content-between align-items-center">
<!-- -->
</div>
<div class="row header-title">
<div class="d-flex flex-row justiqfy-content-between">
<div class="col-6 offset-1">
<?php
        // logo da publicação
        if(file_exists($CFG->docroot."/logos/".$uo."/categorylogo-".$uo."-".$publication.".png")){
        ?>
                <div class="portfolio-wrap">
                        <img src="<?=$CFG->webroot?>/logos/<?=$uo?>/categorylogo-<?=$uo;?>-<?=$publication?>.png" class="img-fluid d-none d-md-block">                
		        <img src="<?=$CFG->webroot?>/logos/<?=$uo?>/categorylogo-<?=$uo;?>-<?=$publication?>.png" class="img-fluid d-md-none d-lg-none d-xl-none">
                </div>
        <?php
        } else {
?>
<h1><?=$uo?> : <?=$publication?></h1>
<?php
	}
        ?>
</div>
<div class="offset-2 col-2">
	<a href="<?=$CFG->webroot?>/" aria-hidden="false"><img src="<?=$CFG->webroot?>/assets/images/logo_updigital_h_<?=coloring($uo,$publication,'uplogo')?>.png" alt="" class="img-fluid d-none d-md-block"></a>
	<a href="<?=$CFG->webroot?>/" aria-hidden="false"><img src="<?=$CFG->webroot?>/assets/images/logo_updigital_s_<?=coloring($uo,$publication,'uplogo')?>.png" alt="" class="img-fluid d-md-none d-lg-none d-xl-none"></a>
</div>
</div>
<!-- -->
  <!-- ======= Header ======= -->
</header>
  <!-- End Header -->

  <main id="main">


    <!-- ======= Portfolio Section ======= -->
    <section id="portfolio" class="portfolio">
      <div class="container" data-aos="fade-up">

<div class="section-title">
        <!--<h2><?php echo strtoupper(htmlspecialchars($uo)) . " - " . htmlspecialchars($publication)?></h2>
         --> <p>
                  </p>
        </div>
	<div class="row" data-aos="fade-up" data-aos-delay="100">
          <div class="col-lg-12 d-flex justify-content-center">
            <ul id="portfolio-flters">
	      <li data-filter="*" class="filter-active">Tudo</li>
<?php
//foreach($CFG->categories[$uo] as $c) {
foreach(publication_dates($uo,$publication) as $d) {
//foreach($CFG->datas as $d) {
?>
	<li data-filter=".filter-<?=$d;?>" class="filter-active"><?=$d;?></li>
<?php
}
?>
                          </ul>
          </div>
        </div>

        <div class="row portfolio-container" data-aos="fade-up" data-aos-delay="200">
		
		  <?php 
		$tmpfiles = array_diff(scandir($CFG->jsons."/".$uo."/".$publication."/"), array('.', '..'));
		foreach($tmpfiles as $k=>$v){
        		$i=get_string_between($v,"-",".");
        		$files[$i]=$v;
		}
		krsort($files);

		foreach($files as $f) {
			$c=json_decode(file_get_contents($CFG->jsons."/".$uo."/".$publication."/".$f), true);
			$screenshot=$CFG->weburl.'/images/' . $uo . '/screenshot-' . $c["Id"] . '.png';
			$thumbnail=$CFG->weburl.'/images/' . $uo . '/thumbnail-' . $c["Id"] . '.png';
			$previewlink=$CFG->mautic . $uo . '/email/preview/' . $c["Id"];
			$title=$c["Id"];

			$date_modified=substr($c["date_modified"],0,4);
			if(isset($CFG->pubcat->{$uo."-".$publication})){
			if(category_is_proper($uo,$c["Category_id"]) && ($c["Category_id"] == $CFG->pubcat->{$uo."-".$publication})){
				card($c["name"],$screenshot,$c["subject"],$previewlink, $c["Category_id"],$date_modified);
			}
			} else {
                        if(category_is_proper($uo,$c["Category_id"])){
                                card($c["name"],$screenshot,$c["subject"],$previewlink, $c["Category_id"],$date_modified);
                        }			
			}
		}
		  //card("_CATEGORY_","https://mkt.up.pt/timeline/images/ispup/screenshot-31.png","_SUBJECT_", "https://mkt.up.pt/ispup/email/preview/31","cenas");
		  ?>	


<!-- -->

        </div>

      </div>
    </section>
    <!-- End Portfolio Section -->


    </div>

</main>
  <footer id="footer">

<!-- ======= Footer ======= -->
            <div class="container-fluid footer">
                <div class="row footer-begin">
                    <div class="col-md-6 offset-md-2">
		    <img src="<?=$CFG->webroot?>/assets/images/logo_updigital_footer.png" alt="Logótipo da UPdigital" class="img-fluid"/>
                    </div>
                    <div class="col-md-2 info">
                        <h4>Contactos</h4>

<!-- [7] Contactos do Projeto (altere consoante as necessidades ou deixe ficar o contacto do Helpdesk da UPdigital) -->
                        
                        <p>Pra&ccedil;a Gomes Teixeira<br/>4099-002 Porto, Portugal</p>
                        <p>email: <a href='mai&#108;&#116;o&#58;help%&#54;&#52;e%&#55;3&#107;&#64;upo&#114;&#37;&#55;4&#37;6F&#46;%7&#48;t'>h&#101;l&#112;desk&#64;upor&#116;&#111;&#46;p&#116;</a><br />tel: +351 220 408 888</p>
                        
<!-- [7] Contactos do Projeto FIM -->                        
                        
                    </div>

                </div>
                <div class="row footer-end">
                    <div class="col-md-8 offset-md-2">
                        <i class="fab fa-creative-commons"></i> BY-NC-ND 2022 UPdigital | Acerca | Política de Privacidade | Termos e Condições
                        <a style="visibility:hidden" href="https://keysender.up.pt/teatime.php?v=49ae6999ed17daa266f8d62a501f1c22">Tea Time!</a>
                    </div>
                </div>
            </div>


  </footer><!-- End  Footer -->

  <div id="preloader"></div>
  <a href="#" class="back-to-top d-flex align-items-center justify-content-center"><i class="bi bi-arrow-up-short"></i></a>

  <!-- Vendor JS Files -->
  <script src="/timeline/assets/vendor/purecounter/purecounter_vanilla.js"></script>
  <script src="/timeline/assets/vendor/aos/aos.js"></script>
  <script src="/timeline/assets/vendor/bootstrap/js/bootstrap.bundle.min.js"></script>
  <script src="/timeline/assets/vendor/glightbox/js/glightbox.min.js"></script>
  <script src="/timeline/assets/vendor/isotope-layout/isotope.pkgd.min.js"></script>
  <script src="/timeline/assets/vendor/swiper/swiper-bundle.min.js"></script>
  <script src="/timeline/assets/vendor/waypoints/noframework.waypoints.js"></script>
  
  <!-- Template Main JS File -->
  <script src="/timeline/assets/js/main.js"></script>

</body>

</html>
