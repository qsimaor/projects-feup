<?php
require_once('/opt/mkt_home/conf/config.php');
//require_once($CFG->libroot.'/security.php');

function index_card_button($uo,$publication){
?>
<a type="button" class="btn btn-sm btn-outline-light" href="<?=$CFG->webroot?>/<?=$uo?>/<?=$publication?>"><?=strtoupper($publication)?></a>
<?php	
}

function index_card($uo){
	
?>
<div id="card" class="col-md-2">
  <div id="card2" name="<?=$uo?>" class="card">
<h2><?=strtoupper($uo)?></h2>
<p class="card-text text-right">
<?php
foreach(list_publications($uo) as $p){
	?>
<a type="button" class="btn btn-sm btn-outline-light" href="<?=$CFG->webroot?>/<?=$uo?>/<?=$p?>"><?=strtoupper($p)?></a>
	<?php
}
?>
</p>
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

foreach(list_uos() as $uo){
	var_dump(list_publications($uo));
}
