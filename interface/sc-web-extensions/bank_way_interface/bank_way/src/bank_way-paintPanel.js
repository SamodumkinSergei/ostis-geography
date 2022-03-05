/**
 * Paint panel.
 */
Way.PaintPanel = function (containerId) {
    this.containerId = containerId;
};

Way.PaintPanel.prototype = {

    init: function () {
        this._initMarkup(this.containerId);
    },

    _initMarkup: function (containerId) {
        var container = $('#' + containerId);

        var self = this;
        container.append('<div class="sc-no-default-cmd">Way Image component</div>');
		//My agent		
		container.append('<label for="latitude" id="name-latitude">Широта точки</label>');
		container.append('<input id="latitude" type="text" class="form-control-plaintext" placeholder="Value for latitude">');
		container.append('<label for="langitude" id="name-langitude">Долгота точки</label>');
		container.append('<input id="langitude" type="text" class="form-control-plaintext" placeholder="Value for langitude">');
		container.append('<label for="bank" id="name-bank">Название отделения банка</label>');
		container.append('<input id="bank" type="text" class="form-control-plaintext" placeholder="Name for bank">');
		container.append('<script src="https://requirejs.org/docs/release/2.3.6/minified/require.js"></script>');
		//button
		container.append('<button id="showPicture" type="button">Показать путь</button>');
      
		$('#showPicture').click(function () {
			if(document.getElementById('latitude').value && document.getElementById('bank').value && document.getElementById('langitude').value){
				self._watchPicture(document.getElementById('latitude').value, document.getElementById('bank').value, document.getElementById('langitude').value, container);
			}
		});
    },

	_watchPicture: function (latitude, bank, langitude, container)
	{
		async function getCoord(latitude, bank, langitude) {
  			try {
    			const url = "https://api.allorigins.win/get?url=" + encodeURIComponent("https://www.openstreetmap.org/geocoder/search_osm_nominatim?query=" + bank + "&callback?=");
				xmlhttp = new XMLHttpRequest();
				xmlhttp.onreadystatechange=function(){
					if(xmlhttp.readyState==4 && xmlhttp.status==200)
					{
						console.log(xmlhttp.responseText);
						var array1 = parseText(xmlhttp.responseText);
						var array2 = [latitude, langitude];
						console.log(array1);
						console.log(array2);
						Promise.all([array1, array2]).then(coord => {
									console.log(coord);
									getPhoto(coord[0], coord[1], container);
								});
								
						return array1;	
					}
				}
				xmlhttp.open("GET", url, false );
				xmlhttp.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
				xmlhttp.send();
  			} catch (error) {
    			console.error(error);
  			}
		}
		
		async function parseText(responseText) {
  			try {
    			var parser = new DOMParser();
				var xmlDoc = parser.parseFromString(xmlhttp.responseText, "text/html");
				var list = xmlDoc.evaluate("//a/@data-lat", xmlDoc, null, XPathResult.ANY_TYPE, null);
				var array = [list.iterateNext().textContent.replaceAll('\\', '').replaceAll('\"', '')];
				var list = xmlDoc.evaluate("//a/@data-lon", xmlDoc, null, XPathResult.ANY_TYPE, null);
				array.push(list.iterateNext().textContent.replaceAll('\\', '').replaceAll('\"', ''));
				return array;
  			} catch (error) {
    			console.error("Invalid coordinates or bank name");
  			}
		}
		
		async function getPhoto(coord1, coord2, container) {
  			try {
				if(coord1 && coord2){
    				const image_url = "http://image.thum.io/get/width/4096/crop/3072/" + "https://www.openstreetmap.org/directions?engine=graphhopper_car&route=" + coord1[0] + "%2C" + coord1[1] + "%3B" + coord2[0] + "%2C" + coord2[1];
					console.log(image_url);
					image_src = "<img src=\"" + image_url + "\" id=\"img_id\"></img>";
					if(document.getElementById("img_id")){
						document.getElementById("img_id").src=image_url
					}
					else{
						container.append(image_src);
					}
				}
  			} catch (error) {
    			console.error("Invalid coordinates or bank name");
  			}
		}

		async function start(latitude, bank, langitude) {
			try{
				await getCoord(encodeURIComponent(latitude), encodeURIComponent(bank), encodeURIComponent(langitude));
			} catch (error) {
    			console.error("Invalid coordinates or bank name");
  			}
		}
		start(latitude, bank, langitude);
	}	
};
