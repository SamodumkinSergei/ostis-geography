<?php
	require_once("vendor/autoload.php");
    $resourceURL = "https://www.openstreetmap.org";
    $keywords = cfg_get("keywords");
    $kbPath = cfg_get("kbPath");
    if (!file_exists($kbPath)) { 
        mkdir($kbPath, 0777, true);
    }

    $pageUrls = array();
    $pageUrl = $resourceURL . "/geocoder/search_osm_nominatim?query=".urlencode($keywords)."+Belarus";
    
    array_push($pageUrls, $pageUrl);

    for ($i = 0; $i < count($pageUrls); $i++){
    $pageUrl = $pageUrls[$i];
    $html = file_get_contents($pageUrl);
	phpQuery::newDocument($html);

    $nextPageUrl = $resourceURL . pq(".btn-primary")->attr("href");
    if ($nextPageUrl != $resourceURL){
        array_push($pageUrls, $nextPageUrl);
    }

    $links = pq(".results-list")->find("li");
    
    foreach ($links as $link){
        $linkData = array();
        $type = pq($link)->text();
        if(!preg_match("/Recycling Point/ui", $type)) 
            continue;

        $link = pq($link)->find("a");

        $region = $link->attr("data-name");
        if(preg_match("/минск/ui", $region)) 
            $region = "minsk";
        else if(preg_match("/витебск/ui", $region)) 
            $region = "vitebsk_region";
        else if(preg_match("/брест/ui", $region)) 
            $region = "brest_region";
        else if(preg_match("/гомель/ui", $region)) 
            $region = "gomel_region";
        else if(preg_match("/гродн/ui", $region)) 
            $region = "grodno_region";
        else if(preg_match("/могил(е|ё)в/ui", $region)) 
            $region = "mogilev_region";

        $url = $resourceURL. $link->attr("href");
        $html = file_get_contents($url);

        phpQuery::newDocument($html);
        
        $data = array(
            "id" => pq("#sidebar_content")->find("bdi:eq(1)")->text(),
            "name" => pq("#sidebar_content")->find("bdi:eq(0)")->text(),
            "latitude" => pq(".latitude")->text(),
            "longitude" => pq(".longitude")->text(),
            "region" => $region
        );
        $data["name_en"] = translit($data["name"]);

        // ----------------- FILE CREATING ---------------------

        if ($data["name"] != ""){
            $fileName = "recycling_point_".$data['id'].".scs";
            $filePath = $kbPath."/".$fileName;
            $text = 'recycling_point_'.$data["id"].' 
    <- concept_recycling_point;
';

        if ($data["name"] != ""){
            $text = $text . '=> nrel_main_idtf: 
    ['.$data["name"].'] (* <- lang_ru;; <- name_ru;; <- name;;*);
=> nrel_main_idtf: 
    ['.$data["name_en"].'] (* <- lang_en;; *);
';
        }

        $text = $text . '=> nrel_search_area: '.$data["region"].';;
';

        $file = fopen($filePath, 'w');
        fwrite($file, $text);
        fclose($file);
        echo $fileName . " created \n";
        }
    }
}
    phpQuery::unloadDocuments();

?>


<?php
  function translit($str) {
    $rus = array('А', 'Б', 'В', 'Г', 'Д', 'Е', 'Ё', 'Ж', 'З', 'И', 'Й', 'К', 'Л', 'М', 'Н', 'О', 'П', 'Р', 'С', 'Т', 'У', 'Ф', 'Х', 'Ц', 'Ч', 'Ш', 'Щ', 'Ъ', 'Ы', 'Ь', 'Э', 'Ю', 'Я', 'а', 'б', 'в', 'г', 'д', 'е', 'ё', 'ж', 'з', 'и', 'й', 'к', 'л', 'м', 'н', 'о', 'п', 'р', 'с', 'т', 'у', 'ф', 'х', 'ц', 'ч', 'ш', 'щ', 'ъ', 'ы', 'ь', 'э', 'ю', 'я', 'ў');
    $lat = array('A', 'B', 'V', 'G', 'D', 'E', 'E', 'Zh', 'Z', 'I', 'Y', 'K', 'L', 'M', 'N', 'O', 'P', 'R', 'S', 'T', 'U', 'F', 'H', 'C', 'Ch', 'Sh', 'Sch', '', 'Y', '', 'E', 'Yu', 'Ya', 'a', 'b', 'v', 'g', 'd', 'e', 'e', 'zh', 'z', 'i', 'y', 'k', 'l', 'm', 'n', 'o', 'p', 'r', 's', 't', 'u', 'f', 'h', 'c', 'ch', 'sh', 'sch', '', 'y', '', 'e', 'yu', 'ya', 'u');
    return str_replace($rus, $lat, $str);
  }

  function cfg_get($option) {
	preg_match('/'.$option.' = \".*\"/', file_get_contents("config"), $value);
	$value =  $value[0];
	$value = preg_replace('/'.$option.' = \"/', "", $value);
	$value = substr($value, 0, -1);
	return $value;
  }
?>
