<?php

require_once('../loader.php');
require_once($CFG->libroot.'/lib.php');

$uo=htmlspecialchars($uo);
$image=htmlspecialchars($image);

print '<img src="'.image_base64_encoded($CFG->docroot."images/".$uo."/".$image.").'">'
