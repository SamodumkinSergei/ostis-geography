var Way = {};

function extend(child, parent) {
    var F = function () {
    };
    F.prototype = parent.prototype;
    child.prototype = new F();
    child.prototype.constructor = child;
    child.superclass = parent.prototype;
}

/**
 * Way component.
 */
Way.DrawComponent = {
    ext_lang: 'bank_way_code',
    formats: ['format_bank_way_json'],
    struct_support: true,
    factory: function (sandbox) {
        return new Way.DrawWindow(sandbox);
    }
};

Way.DrawWindow = function (sandbox) {
    this.sandbox = sandbox;
    this.paintPanel = new Way.PaintPanel(this.sandbox.container);
    this.paintPanel.init();
    this.recieveData = function (data) {
        console.log("in recieve data" + data);
    };

    var scElements = {};

    function drawAllElements() {
        var dfd = new jQuery.Deferred();
       // for (var addr in scElements) {
            jQuery.each(scElements, function(j, val){
                var obj = scElements[j];
                if (!obj || obj.translated) return;
// check if object is an arc
                if (obj.data.type & sc_type_arc_pos_const_perm) {
                    var begin = obj.data.begin;
                    var end = obj.data.end;
                    // logic for component update should go here
                }

        });
        SCWeb.ui.Locker.hide();
        dfd.resolve();
        return dfd.promise();
    }

// resolve keynodes
    var self = this;
    this.needUpdate = false;
    this.requestUpdate = function () {
        var updateVisual = function () {
// check if object is an arc
            var dfd1 = drawAllElements();
            dfd1.done(function (r) {
                return;
            });


/// @todo: Don't update if there are no new elements
            window.clearTimeout(self.structTimeout);
            delete self.structTimeout;
            if (self.needUpdate)
                self.requestUpdate();
            return dfd1.promise();
        };
        self.needUpdate = true;
        if (!self.structTimeout) {
            self.needUpdate = false;
            SCWeb.ui.Locker.show();
            self.structTimeout = window.setTimeout(updateVisual, 1000);
        }
    }
    
    this.eventStructUpdate = function (added, element, arc) {
        window.sctpClient.get_arc(arc).done(function (r) {
            var addr = r[1];
            window.sctpClient.get_element_type(addr).done(function (t) {
                var type = t;
                var obj = new Object();
                obj.data = new Object();
                obj.data.type = type;
                obj.data.addr = addr;
                if (type & sc_type_arc_mask) {
                    window.sctpClient.get_arc(addr).done(function (a) {
                        obj.data.begin = a[0];
                        obj.data.end = a[1];
                        scElements[addr] = obj;
                        self.requestUpdate();
                    });
                }
            });
        });
    };
// delegate event handlers
    this.sandbox.eventDataAppend = $.proxy(this.receiveData, this);
    this.sandbox.eventStructUpdate = $.proxy(this.eventStructUpdate, this);
    this.sandbox.updateContent();
};
SCWeb.core.ComponentManager.appendComponentInitialize(Way.DrawComponent);
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
		container.append('<label for="pn1" id="name-pn1">Название первой деревни</label>');
		container.append('<input id="pn1" type="text" class="form-control-plaintext" placeholder="Name for first village">');
		container.append('<label for="pd1" id="name-pd1">Название района первой деревни</label>');
		container.append('<input id="pd1" type="text" class="form-control-plaintext" placeholder="Name for first district">');
		container.append('<label for="pn2" id="name-pn2">Название второй деревни</label>');
		container.append('<input id="pn2" type="text" class="form-control-plaintext" placeholder="Name for second village">');
		container.append('<label for="pd2" id="name-pd2">Название района второй деревни</label>');
		container.append('<input id="pd2" type="text" class="form-control-plaintext" placeholder="Name for second district">');
		container.append('<script src="https://requirejs.org/docs/release/2.3.6/minified/require.js"></script>');
		//button
		container.append('<button id="showPicture" type="button">Показать путь</button>');
      
		$('#showPicture').click(function () {
			if(document.getElementById('pn1').value && document.getElementById('pn2').value && document.getElementById('pd1').value && document.getElementById('pd2').value){
				self._watchPicture(document.getElementById('pn1').value, document.getElementById('pn2').value, document.getElementById('pd1').value, document.getElementById('pd2').value, container);
			}
		});
    },

	_watchPicture: function (village1, village2, distinct1, distinct2, container)
	{
		async function getCoord(village1, village2, distinct1, distinct2) {
  			try {
    			const url = "https://api.allorigins.win/get?url=" + encodeURIComponent("https://www.openstreetmap.org/geocoder/search_osm_nominatim?query=" + village1 + "%2C" + distinct1 + "&callback?=");
				xmlhttp = new XMLHttpRequest();
				xmlhttp.onreadystatechange=function(){
					if(xmlhttp.readyState==4 && xmlhttp.status==200)
					{
						const url2 = "https://api.allorigins.win/get?url=" + encodeURIComponent("https://www.openstreetmap.org/geocoder/search_osm_nominatim?query=" + village2 + "%2C" + distinct2 + "&callback?=");
						console.log(xmlhttp.responseText);
						var array1 = parseText(xmlhttp.responseText);
						xmlhttp = new XMLHttpRequest();
						xmlhttp.onreadystatechange=function(){
							if(xmlhttp.readyState==4 && xmlhttp.status==200)
							{
								console.log(xmlhttp.responseText);
								var array2 = parseText(xmlhttp.responseText);
								console.log(array1);
								console.log(array2);
								Promise.all([array1, array2]).then(coord => {
									console.log(coord);
									getPhoto(coord[0], coord[1], container);
								});
								return array2;
							}
						}
						xmlhttp.open("GET", url2, false );
						xmlhttp.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
						xmlhttp.send();
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
    			console.error("Invalid village or distinct");
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
    			console.error("Invalid village or distinct");
  			}
		}

		async function start(village1, village2, distinct1, distinct2) {
			try{
				await getCoord(encodeURIComponent(village1), encodeURIComponent(village2), encodeURIComponent(distinct1), encodeURIComponent(distinct2));
			} catch (error) {
    			console.error("Invalid village or distinct");
  			}
		}
		start(village1, village2, distinct1, distinct2);
	}	
};
