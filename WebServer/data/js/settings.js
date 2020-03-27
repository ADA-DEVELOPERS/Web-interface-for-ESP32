$(document).ready(function(){

	var ipInput1 = $('#ipStatic').ipInput();
	var ipInput2 = $('#ipRouter').ipInput();
	var ipInput3 = $('#ipMask').ipInput();
	var ipInput4 = $('#ipDns1').ipInput();
	var ipInput5 = $('#ipDns2').ipInput();

    $.validate();
	AddMyValidator();
	AddMyForm();
	ReadMqtt();
	ReadLan();
	ReadUpgrade();
	ReadConf();
	ReadBD();

});

function ReadMqtt(){
	$.getJSON( "/settings.mqtt.json", function(data){
		$('#mqttIP').val(data["mqttServer"]);
		$('#mqttPort').val(data["mqttPort"]);
		$('#mqttUser').val(data["mqttUser"]);
		$('#mqttPas').val(data["mqttPassword"]);
	});
}

function ReadLan(){
	$.getJSON( "/settings.wifi.json", function(data){
		$("#wifiIp").val(data["ssid"]);
		$("#wifiPas").val(data["password"]);
	});
	
	$.getJSON( "/settings.ap.json", function(data){
		$("#ApIp").val(data["ssidAP"]);
		$("#ApPas").val(data["passwordAP"]);
	});
	
	$.getJSON( "/settings.network.json", function(data){
		$("#ipStatic input.ip1").val(data["apIP"][0]);
		$("#ipStatic input.ip2").val(data["apIP"][1]);
		$("#ipStatic input.ip3").val(data["apIP"][2]);
		$("#ipStatic input.ip4").val(data["apIP"][3]);
		
		$("#ipRouter input.ip1").val(data["gateway"][0]);
		$("#ipRouter input.ip2").val(data["gateway"][1]);
		$("#ipRouter input.ip3").val(data["gateway"][2]);
		$("#ipRouter input.ip4").val(data["gateway"][3]);
		
		$("#ipMask input.ip1").val(data["NMask"][0]);
		$("#ipMask input.ip2").val(data["NMask"][1]);
		$("#ipMask input.ip3").val(data["NMask"][2]);
		$("#ipMask input.ip4").val(data["NMask"][3]);
		
		$("#ipDns1 input.ip1").val(data["primaryDNS"][0]);
		$("#ipDns1 input.ip2").val(data["primaryDNS"][1]);
		$("#ipDns1 input.ip3").val(data["primaryDNS"][2]);
		$("#ipDns1 input.ip4").val(data["primaryDNS"][3]);
		
		$("#ipDns2 input.ip1").val(data["secondaryDNS"][0]);
		$("#ipDns2 input.ip2").val(data["secondaryDNS"][1]);
		$("#ipDns2 input.ip3").val(data["secondaryDNS"][2]);
		$("#ipDns2 input.ip4").val(data["secondaryDNS"][3]);
	});
}

function ReadUpgrade(){
	$.getJSON( "/settings.upgrade.json", function(data){
		$('#url').val(data["URL"]);
		$('#ver').text(data["ver"]);
		//$('#data').val(data["data"]);  Нужно сделать
	});
}

function ReadConf(){
	$.getJSON( "/info.conf.json", function(data){
		$("#moduleMode").val(data["module"]);
		$("#nameMode").val(data["name"]);
		$("#idMode").val(data["host"]);
	});
}

function ReadBD(){
	//Кнопка настройки MQTT
	$('body').on('click', '#setMqtt', function(){
		ReadMqtt();
	});
	
	//Кнопка настройки Сети
	$('body').on('click', '#setLan', function(){
		ReadLan();
	});
	
	//Кнопка Обновлений
	$('body').on('click', '#setUpgrade', function(){
		ReadUpgrade();
	});
	
	//Кнопка настройки Конфигураций
	$('body').on('click', '#setConf', function(){
		ReadConf();
	});

	//Кнопка Перезагрузки
	$(document).on("click", '#reset', function() {
		window.location.href='404.html'
		$.get("/restart?device=ok", {}, function(data){
			alert("Идет перезагрузка");
		});
	});
}

// Add Form
function AddMyForm(){
	// Отправить форму MQTT
	$( "#formMqtt" ).submit(function( event ) {
		var mqttServer = $('#mqttIP').val();
		var mqttPort = $('#mqttPort').val();
		var mqttUser = $('#mqttUser').val();
		var mqttPassword = $('#mqttPas').val();
		if(mqttUser == "") {
			var mqttSave = "/mqttsave?mqttServer=" + mqttServer + "&mqttPort=" + mqttPort;
		} else if (mqttPassword == ""){
			var mqttSave = "/mqttsave?mqttServer=" + mqttServer + "&mqttPort=" + mqttPort + "&mqttUser=" + mqttUser;
		} else {
			var mqttSave = "/mqttsave?mqttServer=" + mqttServer + "&mqttPort=" + mqttPort + "&mqttUser=" + mqttUser + "&mqttPassword=" + mqttPassword;
		}
		$.get(mqttSave, {}, function(data){
			//Нужно сделать ответ
		});
		//event.preventDefault();
	});
	
	// Отправить форму Конфигураций
	$( "#formConf" ).submit(function( event ) {
		var moduleMode = $('#moduleMode').val();
		var nameMode = $('#nameMode').val();
		var idMode = $('#idMode').val();
		var confSave = "/confsave?module=" + moduleMode + "&name=" + nameMode + "&host=" + idMode;
		$.get(confSave, {}, function(data){
			//Нужно сделать ответ
		});
		//event.preventDefault();
	});

	// Отправить форму WIFI
	$( "#formWifi" ).submit(function( event ) {
		var wifiIp = $('#wifiIp').val();
		var wifiPas = $('#wifiPas').val();
		var wifiSave = "/wifisave?ssid=" + wifiIp + "&password=" + wifiPas;
		$.get(wifiSave, {}, function(data){
			//Нужно сделать ответ
		});
		//event.preventDefault();
	});

	// Отправить форму AP
	$( "#formAp" ).submit(function( event ) {
		var ApIp = $('#ApIp').val();
		var ApPas = $('#ApPas').val();
		var ApSave = "/apsave?ssidAP=" + ApIp + "&passwordAP=" + ApPas;
		$.get(ApSave, {}, function(data){
			//Нужно сделать ответ
		});
		//event.preventDefault();
	});

	// Отправить форму Сети
	$('body').on('click', '#btnSaveLan', function(){

		var s1 = $("#ipStatic input.ip1").val();
		var s2 = $("#ipStatic input.ip2").val();
		var s3 = $("#ipStatic input.ip3").val();
		var s4 = $("#ipStatic input.ip4").val();
		
		var r1 = $("#ipRouter input.ip1").val();
		var r2 = $("#ipRouter input.ip2").val();
		var r3 = $("#ipRouter input.ip3").val();
		var r4 = $("#ipRouter input.ip4").val();
		
		var m1 = $("#ipMask input.ip1").val();
		var m2 = $("#ipMask input.ip2").val();
		var m3 = $("#ipMask input.ip3").val();
		var m4 = $("#ipMask input.ip4").val();
		
		var f1 = $("#ipDns1 input.ip1").val();
		var f2 = $("#ipDns1 input.ip2").val();
		var f3 = $("#ipDns1 input.ip3").val();
		var f4 = $("#ipDns1 input.ip4").val();
		
		var d1 = $("#ipDns2 input.ip1").val();
		var d2 = $("#ipDns2 input.ip2").val();
		var d3 = $("#ipDns2 input.ip3").val();
		var d4 = $("#ipDns2 input.ip4").val();


		var LanSave = "/lansave?s1="
			  +s1+"&s2="+s2+"&s3="+s3+"&s4="+s4+
		"&r1="+r1+"&r2="+r2+"&r3="+r3+"&r4="+r4+
		"&m1="+m1+"&m2="+m2+"&m3="+m3+"&m4="+m4+
		"&f1="+f1+"&f2="+f2+"&f3="+f3+"&f4="+f4+
		"&d1="+d1+"&d2="+d2+"&d3="+d3+"&d4="+d4;
		
		$.get(LanSave, {}, function(data){
			//Нужно сделать ответ
		});
		//event.preventDefault();
	});
}

// Add validator
function AddMyValidator(){
	
    $.formUtils.addValidator({
		name:"server",
		validatorFunction:function(a){
			return a.length>0&&a.length<=253&&!/[^a-zA-Z0-9]/.test(a.slice(-2))&&!/[^a-zA-Z0-9]/.test(a.substr(0,1))&&!/[^a-zA-Z0-9\.\-]/.test(a)&&1===a.split("..").length&&a.split(".").length>1
		},
		errorMessage:"Некорректный сервер",
		errorMessageKey:"Некорректный сервер"
	}),
	
	$.formUtils.addValidator({
        name : 'port',
        validatorFunction : function(value, $el, config, language, $form) {
            return $.isNumeric(value);
        },
        errorMessage : 'Вводите правильный порт',
        errorMessageKey: 'Вводите правильный порт'
    });
	
	$.formUtils.addValidator({
		name:"strENnullpass",
		validatorFunction:function(b,c,d,e){
			if(b == "") {
				return true;
			}
			if (b.length > 7) {
				var f = "^([a-zA-Z0-9]+)$";
				this.errorMessage="Некорректный ввод";
				return new RegExp(f).test(b)
			} else {
				this.errorMessage="Должно быть не менее 8 символов";
				return false;
			}
		},
		errorMessage:"",
		errorMessageKey:""
	}),

	$.formUtils.addValidator({
		name:"strENnull",
		validatorFunction:function(b,c,d,e){
			if (b != "") {
				var f = "^([a-zA-Z0-9]+)$";
				
				this.errorMessage="Некорректный ввод";
				return new RegExp(f).test(b)
			} else {
				return true;
			}
		},
		errorMessage:"",
		errorMessageKey:""
	}),
	
	$.formUtils.addValidator({
		name:"strEN",
		validatorFunction:function(b,c,d,e){
			var f = "^([a-zA-Z0-9]+)$";
			
			this.errorMessage="Некорректный ввод";
			return new RegExp(f).test(b)
		},
		errorMessage:"",
		errorMessageKey:""
	}),
	
	$.formUtils.addValidator({
		name:"strRU",
		validatorFunction:function(b,c,d,e){
			var f = "^([А-Яа-яa-zA-Z0-9]+)$";
			
			this.errorMessage="Некорректный ввод";
			return new RegExp(f).test(b)
		},
		errorMessage:"",
		errorMessageKey:""
	}),
	
	$.formUtils.addValidator({
		name:"strRUnull",
		validatorFunction:function(b,c,d,e){
			if (b != "") {
				var f = "^([А-Яа-яa-zA-Z0-9]+)$";
				
				this.errorMessage="Некорректный ввод";
				return new RegExp(f).test(b)
			} else {
				return true;
			}
		},
		errorMessage:"",
		errorMessageKey:""
	})
};
