<?php

defined('GEEKTOTHEBONE') || die();

//----------------------------------------------------------------------

function category_name($uo,$cid){
        $ret=$cid;
        if($uo == "feup"){
                switch ($cid) {
                case 11:
                        $ret="Highlights 2022";
                        break;
                case 12:
                        $ret="FEUPWorld";
                        break;
                }
        }

        if($uo == "cultura"){
                switch ($cid) {
                case 2:
                        $ret="Newsletters";
                        break;
                }
        }
        return $ret;
}

function category_is_proper($uo,$categoryId){
        global $CFG;
        $return=FALSE;
        if(!isset($CFG->categories[$uo])) {
                $return=TRUE;
        } else {
        foreach($CFG->categories[$uo] as $c){
                if($categoryId == $c){
                        $return=TRUE;
                        break;
                }
        }
        }
        return $return;
}

function safeRedirect($url, $exit = TRUE) {
        try {
                // Only use the header redirection if headers are not already sent
                if (headers_sent() !== true) {

                        if (strlen(session_id()) > 0) // if using sessions
            {
                session_regenerate_id(true); // avoids session fixation attacks
                session_write_close(); // avoids having sessions lock other requests
            }

                        header('HTTP/1.1 301 Moved Permanently');
                        header('Location: ' . $url);
                        // Optional workaround for an IE bug (thanks Olav)
                        header("Connection: close");
                        exit;
                }
                // HTML/JS Fallback:
                // If the header redirection did not work, try to use various methods other methods
                print '<html>';
                print '<head><title>Redirecting you...</title>';
                print '<meta http-equiv="refresh" content="0;url=' . $url . '" />';
                print '</head>';
                print '<body onload="location.replace(\'' . $url . '\')">';
                // If the javascript and meta redirect did not work,
                // the user can still click this link
                print 'You should be redirected to this URL:<br />';
                print "<a href='$url'>$url</a><br /><br />";
                print 'If you are not, please click on the link above.<br />';
                print '</body>';
                print '</html>';
                // Stop the script here (optional)
                if ($exit) {
                        exit;
                }
        } catch (Exception $err) {
                return $err->getMessage();
        }
}

function uo_is_proper($uo){
        global $CFG;
        $return=FALSE;
        foreach($CFG->instancias as $i){
                if(htmlspecialchars($uo) == $i){
                        $return=TRUE;
                        break;
                }
        }
        return $return;
}
function date_is_proper($date){
        global $CFG;
        $return=FALSE;
        foreach($CFG->datas as $d){
                if(htmlspecialchars($date) == $d){
                        $return=TRUE;
                        break;
                }
        }
        return $return;
}

function publication_is_proper($uo,$publication){
        global $CFG;
	$return=FALSE;
	//echo "<pre>";
	//var_dump($CFG->publications[$uo]);
	//echo "uo: $uo<br>";
	//echo "publication: $publication<br>";
	
	foreach($CFG->publications[$uo] as $k=>$pub){
		//echo "k: $k<br>";
		//echo "pub: $pub<br>";
                if($publication == $pub){
                        $return=TRUE;
                        break;
                }
        }
        return $return;
}

function card($category,$thumbnailImageLink,$subject, $previewLink,$title,$date_modified){
?>
          <div class="col-lg-4 col-md-6 portfolio-item filter-<?=$date_modified;?>">
            <div class="portfolio-wrap">
              <img src="<?=$thumbnailImageLink;?>" class="img-fluid" alt="">
              <div class="portfolio-info"><a href="<?=$previewLink;?>" class="portfolio-details-lightbox" data-glightbox="type: external" title="Preview">
                <h4><?=strtoupper($category);?></h4>
                <p><?=$subject;?></p></a>
                <div class="portfolio-links">
                  <a href="<?=$previewLink;?>" class="portfolio-details-lightbox" data-glightbox="type: external" title="Preview"><i class="bx bx-plus"></i></a>
                </div>
              </div>
            </div>
          </div>
<?php
}

function get_string_between($string, $start, $end){
    $string = ' ' . $string;
    $ini = strpos($string, $start);
    if ($ini == 0) return '';
    $ini += strlen($start);
    $len = strpos($string, $end, $ini) - $ini;
    return substr($string, $ini, $len);
}
// -- index.php (start)
function index_card_button($uo,$publication){
	global $CFG;
?>
<a type="button" class="btn btn-sm btn-outline-light" href="<?=$CFG->webroot?>/<?=$uo?>/<?=$publication?>"><?=strtoupper($publication)?></a>
<?php
}

function index_card($uo){
	global $CFG;
?>
<div id="card" class="col-md-3">
  <div id="card2" name="<?=$uo?>" class="card">
    <div class="row">
      <div class="col">
	<p>&nbsp;</p>
        <h2 class="text-center"><?=strtoupper($uo)?></h2>
        <p class="card-text text-right">
<?php
foreach(list_publications($uo) as $p){
	index_card_button($uo,$p);
}
?>
        </p>
      </div>
    </div>
<div class="row align-items-end">
<div class="col" style="background-color: <?=primary_color($uo)?>; border-top:1px solid black;">&nbsp;</div>
<div class="col" style="background-color: <?=secondary_color($uo)?>; border-top:1px solid black;">&nbsp;</div>
</div>
</div>
</div>
<?php
}

function list_publications($uo){
        global $CFG;
        $publications = array();
        $tmpfiles = array_diff(scandir($CFG->jsons."/".$uo."/"), array('.', '..'));
        foreach($tmpfiles as $k=>$v){
                $publications[] =$v;
        }
        return $publications;
}
function list_uos(){
        global $CFG;
        $uos = array();
        $tmpfiles = array_diff(scandir($CFG->jsons."/"), array('.', '..'));
        foreach($tmpfiles as $k=>$v){
                $uos[] =$v;
        }
        return $uos;
}

function primary_color($uo){
	global $CFG;
	$cores=json_decode(file_get_contents($CFG->home."/conf/cores.json"));

	return $cores->$uo[0]->primary;
	//return "#f00";
}
function secondary_color($uo){
        global $CFG;
	$cores=json_decode(file_get_contents($CFG->home."/conf/cores.json"));

	return $cores->$uo[0]->secondary;
	//return "#00f";
}
function coloring($uo,$publication,$slot){
        global $CFG;
	$cores=json_decode(file_get_contents($CFG->home."/conf/cores.json"));
	foreach($cores->$uo as $k=>$cu){
		//var_dump($cu->$slot);
		//se for a publicação
		if($cu->publication==$publication){
			// se estiver definido a cor do slot da publicação
			//var_dump($slot);
			//return $cu->$slot;
			if(isset($cu->$slot)){
				//var_dump($cu->$slot);
        			return $cu->$slot;
			} else {
				if(isset($cores->default[0]->$slot)){
					return $cores->default[0]->$slot;
				} else {
					return "#107699";
				}
			}
		}

	}
}
function coloringheader($uo,$slot){
	global $CFG;
	$header=$slot.'-banner';
        $cores=json_decode(file_get_contents($CFG->home."/conf/cores.json"));
        if(isset($cores->$uo[0]->$header)){
		return $cores->$uo[0]->$header;
	} else {
		if(isset($cores->$uo[0]->$slot)){
                	return $cores->$uo[0]->$slot;
        	} else {
                	if(isset($cores->default[0]->$slot)){
                        	return $cores->default[0]->$slot;
                	} else {
                        	return "#107699";
                	}
        	}
	}
}

function coloringbuttons($uo){
        global $CFG;
        $cores=json_decode(file_get_contents($CFG->home."/conf/cores.json"));
        if(isset($cores->$uo[0]->buttons)){
                return $cores->$uo[0]->buttons;
        } else {
                if(isset($cores->default[0]->buttons)){
                        return $cores->default[0]->buttons;
                } else {
                        return $cores->default[0]->primary;
                }
        }
}
// ---- index.php (end)
function uplogocolor($uo){
	global $CFG;
	$return="white";
	$cores=json_decode(file_get_contents($CFG->home."/conf/cores.json"));
	if(isset($cores->$uo[0]->uplogo)){
		if(($cores->$uo[0]->uplogo == "black") || ($cores->$uo[0]->uplogo == "white")){
			$return=$cores->$uo[0]->uplogo;
		}
	}
	echo $return;
}

function include_footer(){
	global $CFG;
?>
            <div class="container-fluid footer">
                <div class="row footer-begin">
                    <div class="col-md-6 offset-md-2 info">
                        <h4>UPdigital</h4>

<!-- [7] Contactos do Projeto (altere consoante as necessidades ou deixe ficar o contacto do Helpdesk da UPdigital) -->

                        <p>Pra&ccedil;a do Coronel Pacheco 15<br/>4050-453 Porto, Portugal</p>
                        <p><a href='mai&#108;&#116;o&#58;help%&#54;&#52;e%&#55;3&#107;&#64;upo&#114;&#37;&#55;4&#37;6F&#46;%7&#48;t'>h&#101;l&#112;desk&#64;upor&#116;&#111;&#46;p&#116;</a>  | +351 220 408 888</p>

<!-- [7] Contactos do Projeto FIM -->
                        <img src="<?=$CFG->webroot?>/assets/images/logo_updigital_footer.png" alt="Logótipo da UPdigital" class="img-fluid"/>
                    </div>
                </div>

                <div class="row footer-end">
                    <div class="col-md-8">
                        &copy; 2022 UPdigital | <a href="<?=$CFG->webroot?>/about">Sobre</a> | <a href="<?=$CFG->webroot?>/policy">Política de Privacidade</a> | <a href="<?=$CFG->webroot?>/conditions">Termos e Condi&ccedil;&otilde;es</a>
			<a style="visibility:hidden" href="https://mkt.up.pt/timeline/418?v=<?=generateFormToken(random_int(100, 999))?>">Tea Time!</a>
		    </div>
                    <div class="col-md-1 offset-md-1">
		    	Vers&atilde;o 0.0.7 (BETA)
		    </div>
                </div>
            </div>


  </footer>
<?php
}
function publication_dates($uo,$publication){

	global $CFG;


	$datas=json_decode(file_get_contents($CFG->home."/conf/config.json"));
	$index=0;
	foreach($datas->$uo as $k=>$v) {
		if($v->publication==$publication){
			$index=$k;
			break;
		}
	
	}
	if(isset($datas->$uo[$index]->date_start)){
			$date_start=$datas->$uo[$index]->date_start;
	} else {
		$date_start=array_pop(array_reverse($CFG->datas));
	}
	// se o json tive date_end=0, fazer fim o ano atual
	if(isset($datas->$uo[$index]->date_end)){
		if($datas->$uo[$index]->date_end == 0){
			$date_end=date("Y");
		} else {
			$date_end=$datas->$uo[$index]->date_end;
		}
	} else {
		//$datas=$CFG->datas;
		//$date_end=array_pop($datas);
		$date_end=date("Y");
	}
	//print_r($date_end);
	for($i=$date_start; $i<=$date_end; $i++) {
		$return[] = $i;	
	}
	//print_r($return);
	return $return;
	
}
