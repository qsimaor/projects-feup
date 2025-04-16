<?php

$cores=json_decode(file_get_contents("cores.json"));

//var_dump($cores->fep[0]->secondary);
$uo="icbas";
$slot="newsletter";
        foreach($cores->$uo as $k=>$cu){
		var_dump($cu->publication);
		echo "\n";
                if($cu->publication==$slot){
                        if(isset($cu->banner)){
                                echo $cu->banner;
                        } else {
                        if(isset($cores->default[0]->$slot)){
                                echo $cores->default[0]->$slot;
                        } else {
                                echo "#00365e";
                        }
                }
        }

        }
