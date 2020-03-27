jQuery(document).ready(function($) {
	$(document).ready(function(){
		
		StstusBar();

		$.getJSON( "/settings.network.json", function(data){
			var i = data["apIP"]
			$('#wifi').text( i[0] + "." + i[1] + "." + i[2] + "." + i[3] );
		});
		
		$.getJSON( "/settings.mqtt.json", function(data){
			$('#mqtt').text(data["mqttServer"]);
		});
		
		$('#home').text("0.0.0.0");//Необходимо реализовать соединение с умным домом
		
		$.getJSON( "/info.weather.json", function(data){
			$('#temperature').text(data["Temperature"]);
			$('#pressure').text(data["Pressure"]);
			$('#humidity').text(data["Humidity"]);
			$('#altitude').text(data["Altitude"]);
		});
		
	});
});

function StstusBar(){
	$.getJSON( "/info.status.json", function(data){
		
		if(data["home"] == "on") {
			$("#homepng").attr("src","images/homeon.png");
		} else if(data["home"] == "search"){
			$("#homepng").attr("src","images/homesearch.png");
		} else if(data["home"] == "off"){
			$("#homepng").attr("src","images/homeoff.png");
		}
		
		
		if(data["wifi"] == "on") {
			$("#wifipng").attr("src","images/wifion.png");
		} else if(data["wifi"] == "search"){
			$("#wifipng").attr("src","images/wifisearch.png");
		} else if(data["wifi"] == "off"){
			$("#wifipng").attr("src","images/wifioff.png");
		}
		
		
		if(data["mqtt"] == "on") {
			$("#mqttpng").attr("src","images/mqtton.png");
		} else if(data["mqtt"] == "search"){
			$("#mqttpng").attr("src","images/mqttsearch.png");
		} else if(data["mqtt"] == "off"){
			$("#mqttpng").attr("src","images/mqttoff.png");
		}
			
	});
}


window.setInterval(function(){
	$.getJSON( "/info.weather.json", function(data){
			$('#temperature').text(data["Temperature"]);
			$('#pressure').text(data["Pressure"]);
			$('#humidity').text(data["Humidity"]);
			$('#altitude').text(data["Altitude"]);
	});
	
	StstusBar();
}, 15000);