var MapKeynodes = {
  
}

MapKeynodes.IDENTIFIERS = [
  'nrel_main_idtf',
  'lang_ru',
  'rrel_key_sc_element',
  'sc_illustration',
  'sc_definition',
  'nrel_sc_text_translation',
  'rrel_example',
  'nrel_osm_query',
  'ui_menu_file_for_finding_persons'
];

MapKeynodes.init = function() {
  var deferred = $.Deferred();
  var self = this;
  SCWeb.core.Server.resolveScAddr(MapKeynodes.IDENTIFIERS, function (keynodes) {
    self.keynodes = keynodes;
    deferred.resolve();
  });
  return deferred;
};


MapKeynodes.get = function(identifier) {
  return this.keynodes[identifier];
};