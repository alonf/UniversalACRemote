#pragma once
#include <String>
#ifndef _ACVIEW_h
#define _ACVIEW_h
#include "Configuration.h"

/*
 * Since the view is different between the AC types, there is a different template for each of them.
 * In the future, a conditional element can be added to build a complex combined template
 */
#ifdef ELECTRA
const static char ACViewHtmlTemplate[] PROGMEM = R"(
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title><%=Title%></title>
<link rel="stylesheet" type="text/css" href="view.css" media="all">
</head>
<body id="main_body">
	<div id="form_container">
		<h1><a><%=Title%></a></h1>
		<form id="form_39821" class="appnitro"  method="post" action="sendacstate">
		    <div class="form_description">
			    <h2><%=Title%>&emsp;Room:&nbsp;<%=RoomTemperature%>&deg;c&emsp;Humidity:&nbsp;<%=RoomHumidity%>&percnt;</h2>
		        <input type="hidden" name="ApiKey" value="<%=ApiKey%>"></input>
		    </div>						
		<ul >
		<li>
		<label class="description" for="ACMode">Air Conditioner Mode </label>
		<span>
			<input id="ACModeAuto" name="ACMode" class="element radio" type="radio" value="AUTO" <%=ACModeAuto%>/>
            <label class="choice" for="ACModeAuto">Auto</label>
		    <input id="ACModeCool" name="ACMode" class="element radio" type="radio" value="COOL" <%=ACModeCool%> />
            <label class="choice" for="ACModeCool">Cool</label>
            <input id="ACModeHeat" name="ACMode" class="element radio" type="radio" value="HEAT" <%=ACModeHeat%>/>
            <label class="choice" for="ACModeHeat">Heat</label>
            <input id="ACModeFan" name="ACMode" class="element radio" type="radio" value="FAN" <%=ACModeFan%> />
            <label class="choice" for="ACModeFan">Fan</label>
            <input id="ACModeDry" name="ACMode" class="element radio" type="radio" value="DRY" <%=ACModeDry%>/>
            <label class="choice" for="ACModeDry">Dry</label>
		</span> 
		</li>		
        <li>
		<label class="description" for="ACFan">Fan Speed </label>
		<span>
			<input id="FanModeAuto" name="ACFan" class="element radio" type="radio" value="AUTO" <%=FanModeAuto%> />
            <label class="choice" for="FanModeAuto">Auto</label>
            <input id="FanModeLow" name="ACFan" class="element radio" type="radio" value="LOW" <%=FanModeLow%> />
            <label class="choice" for="FanModeLow">Low</label>
            <input id="FanModeMedium" name="ACFan" class="element radio" type="radio" value="MEDIUM" <%=FanModeMedium%> />
            <label class="choice" for="FanModeMedium">Medium</label>
            <input id="FanModeHigh" name="ACFan" class="element radio" type="radio" value="HIGH" <%=FanModeHigh%> />
            <label class="choice" for="FanModeHigh">High</label>
		</span> 
		</li>		
        <li>
		<label class="description" for="operations">Operations</label>
		<span id="operations">
			<input id="IsSwingOn" name="IsSwingOn" class="element checkbox" type="checkbox" value="true" <%=Swing%>/>
            <label class="choice" for="IsSwingOn">Swing</label>
            <input id="IsSleepOn" name="IsSleepOn" class="element checkbox" type="checkbox" value="true" <%=Sleep%> />
            <label class="choice" for="IsSleepOn">Sleep</label>
            <input id="IsiFeelOn" name="IsiFeelOn" class="element checkbox" type="checkbox" value="true" <%=iFeel%> />
            <label class="choice" for="IsiFeelOn">iFeel</label>
            <input id="IsPowerOn" name="IsPowerOn" class="element checkbox" type="checkbox" value="true" <%=PowerOn%> />
            <label class="choice" for="IsPowerOn">Power On</label>
		</span> 
		</li>		
        <li>
		<label class="description" for="Temperature">Temperature </label>
		<div>
			<input id="Temperature" name="Temperature" class="element text medium" type="text" maxlength="255" value="<%=Temperature%>"/> 
		</div> 
		</li>
			<li class="buttons">
			<input type="hidden" name="form_id" value="39821" />
			<input id="saveForm" class="button_text" type="submit" name="submit" value="Submit" />
		</li>
	    </ul>
		</form>	
	</div>
	</body>
</html>
)";
#elif defined(TADIRAN)
const static char ACViewHtmlTemplate[] PROGMEM = R"(
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title><%=Title%></title>
<link rel="stylesheet" type="text/css" href="view.css" media="all">
</head>
<body id="main_body">
	<div id="form_container">
		<h1><a><%=Title%></a></h1>
		<form id="form_39821" class="appnitro"  method="post" action="sendacstate">
		    <div class="form_description">
			    <h2><%=Title%>&emsp;Room:&nbsp;<%=RoomTemperature%>&deg;c&emsp;Humidity:&nbsp;<%=RoomHumidity%>&percnt;</h2>
		        <input type="hidden" name="ApiKey" value="<%=ApiKey%>"></input>
		    </div>						
		<ul >
		<li>
		<label class="description" for="ACMode">Air Conditioner Mode </label>
		<span>
			<input id="ACModeCool" name="ACMode" class="element radio" type="radio" value="COOL" <%=ACModeCool%> />
            <label class="choice" for="ACModeCool">Cool</label>
            <input id="ACModeHeat" name="ACMode" class="element radio" type="radio" value="HEAT" <%=ACModeHeat%>/>
            <label class="choice" for="ACModeHeat">Heat</label>
            <input id="ACModeFan" name="ACMode" class="element radio" type="radio" value="FAN" <%=ACModeFan%> />
            <label class="choice" for="ACModeFan">Fan</label>
            <input id="ACModeHumid" name="ACMode" class="element radio" type="radio" value="HUMID" <%=ACModeHumid%>/>
            <label class="choice" for="ACModeHumid">Humid</label>
            <input id="ACModeRecycle" name="ACMode" class="element radio" type="radio" value="RECYCLE" <%=ACModeRecycle%>/>
            <label class="choice" for="ACModeRecycle">Recycle</label>
		</span> 
		</li>		
        <li>
		<label class="description" for="ACFan">Fan Speed</label>
		<span>
			<input id="FanModeAuto" name="ACFan" class="element radio" type="radio" value="AUTO" <%=FanModeAuto%> />
            <label class="choice" for="FanModeAuto">Auto</label>
            <input id="FanModeLow" name="ACFan" class="element radio" type="radio" value="LOW" <%=FanModeLow%> />
            <label class="choice" for="FanModeLow">Low</label>
            <input id="FanModeMedium" name="ACFan" class="element radio" type="radio" value="MEDIUM" <%=FanModeMedium%> />
            <label class="choice" for="FanModeMedium">Medium</label>
            <input id="FanModeHigh" name="ACFan" class="element radio" type="radio" value="HIGH" <%=FanModeHigh%> />
            <label class="choice" for="FanModeHigh">High</label>
            <input id="FanModeTurbo" name="ACFan" class="element radio" type="radio" value="TURBO" <%=FanModeTurbo%> />
            <label class="choice" for="FanModeTurbo">Turbo</label>
		</span> 
		</li>
        <li>
		<label class="description" for="Operations">Operations</label>
		<span>
			<input id="IsSwingOn" name="IsSwingOn" class="element checkbox" type="checkbox" value="true" <%=Swing%>/>
            <label class="choice" for="IsSwingOn">Swing</label>
            <input id="IsXFanOn" name="IsXFanOn" class="element checkbox" type="checkbox" value="true" <%=XFan%> />
            <label class="choice" for="IsXFanOn">XFan</label>
            <input id="IsLightOn" name="IsLightOn" class="element checkbox" type="checkbox" value="true" <%=Light%> />
            <label class="choice" for="IsLightOn">Light</label>
            <input id="IsPowerOn" name="IsPowerOn" class="element checkbox" type="checkbox" value="true" <%=PowerOn%> />
            <label class="choice" for="IsPowerOn">Power On</label>
		</span> 
        </li>
        <li>
            <label class="description">Swing Mode</label>
                <span>
                <input id="SW_1" name="ExtendedSwingMode" class="element radio" type="radio" value="OFF" <%=ACExtendedSwingModeOff%> />
                <label class="choice" for="SW_1">Off</label>
                <input id="SW_2" name="ExtendedSwingMode" class="element radio" type="radio" value="ONFULL" <%=ACExtendedSwingModeOnFull%> />
                <label class="choice" for="SW_2">On Full</label>
                <input id="SW_3" name="ExtendedSwingMode" class="element radio" type="radio" value="ON1" <%=ACExtendedSwingModeOn1%> />
                <label class="choice" for="SW_3">On 1</label>
                <input id="SW_4" name="ExtendedSwingMode" class="element radio" type="radio" value="ON2" <%=ACExtendedSwingModeOn2%> />
                <label class="choice" for="SW_4">On 2</label>
                <input id="SW_5" name="ExtendedSwingMode" class="element radio" type="radio" value="ON3" <%=ACExtendedSwingModeOn3%> />
                <label class="choice" for="SW_5">On 3</label>
                <input id="SW_6" name="ExtendedSwingMode" class="element radio" type="radio" value="ON4" <%=ACExtendedSwingModeOn4%> />
                <label class="choice" for="SW_6">On 4</label>
                <input id="SW_7" name="ExtendedSwingMode" class="element radio" type="radio" value="ON5" <%=ACExtendedSwingModeOn5%> />
                <label class="choice" for="SW_7">On 5</label>
                <input id="SW_8" name="ExtendedSwingMode" class="element radio" type="radio" value="ONFULLLOWER" <%=ACExtendedSwingModeOnFullLower%> />
                <label class="choice" for="SW_8">On Full Lower</label>
                <input id="SW_9" name="ExtendedSwingMode" class="element radio" type="radio" value="ONFULLMIDDLE" <%=ACExtendedSwingModeOnFullMiddle%> />
                <label class="choice" for="SW_9">On Full Middle</label>
                <input id="SW_10" name="ExtendedSwingMode" class="element radio" type="radio" value="ONFULLUPPER" <%=ACExtendedSwingModeOnFullUpper%> />
                <label class="choice" for="SW_10">On Full Upper</label>
		        </span> 
		</li>
        <li>
		<label class="description" for="Temperature">Temperature </label>
		<div>
			<input id="Temperature" name="Temperature" class="element text medium" type="text" maxlength="255" value="<%=Temperature%>"/> 
		</div> 
		</li>
		<li class="buttons">
		    <input type="hidden" name="form_id" value="39821" />
			<input id="saveForm" class="button_text" type="submit" name="submit" value="Submit" />
		</li>
		</ul>
		</form>	
	</div>
	</body>
</html>
)";
#elif defined(TADIRANTAC290)
const static char ACViewHtmlTemplate[] PROGMEM = R"(
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title><%=Title%></title>
<link rel="stylesheet" type="text/css" href="view.css" media="all">
</head>
<body id="main_body">
	<div id="form_container">
		<h1><a><%=Title%></a></h1>
		<form id="form_39821" class="appnitro"  method="post" action="sendacstate">
		    <div class="form_description">
			    <h2><%=Title%>&emsp;Room:&nbsp;<%=RoomTemperature%>&deg;c&emsp;Humidity:&nbsp;<%=RoomHumidity%>&percnt;</h2>
		        <input type="hidden" name="ApiKey" value="<%=ApiKey%>"></input>
		    </div>						
		<ul >
		<li>
		<label class="description" for="ACMode">Air Conditioner Mode </label>
		<span>
		    <input id="ACModeCool" name="ACMode" class="element radio" type="radio" value="COOL" <%=ACModeCool%> />
            <label class="choice" for="ACModeCool">Cool</label>
            <input id="ACModeHeat" name="ACMode" class="element radio" type="radio" value="HEAT" <%=ACModeHeat%>/>
            <label class="choice" for="ACModeHeat">Heat</label>
		</span> 
		</li>		
        <li>
		<label class="description" for="ACFan">Fan Speed </label>
		<span>
           <input id="FanModeLow" name="ACFan" class="element radio" type="radio" value="LOW" <%=FanModeLow%> />
            <label class="choice" for="FanModeLow">Low</label>
           <input id="FanModeTurbo" name="ACFan" class="element radio" type="radio" value="TURBO" <%=FanModeTurbo%> />
            <label class="choice" for="FanModeTurbo">Turbo</label>
		</span> 
		</li>		
        <li>
		<label class="description" for="operations">Operations</label>
		<span id="operations">
            <input id="IsPowerOn" name="IsPowerOn" class="element checkbox" type="checkbox" value="true" <%=PowerOn%> />
            <label class="choice" for="IsPowerOn">Power On</label>
		</span> 
		</li>		
        <li>
		<label class="description" for="Temperature">Temperature </label>
		<div>
			<input id="Temperature" name="Temperature" class="element text medium" type="text" maxlength="255" value="<%=Temperature%>"/> 
		</div> 
		</li>
			<li class="buttons">
			<input type="hidden" name="form_id" value="39821" />
			<input id="saveForm" class="button_text" type="submit" name="submit" value="Submit" />
		</li>
	    </ul>
		</form>	
	</div>
	</body>
</html>
)";
#else
#error("One AC type must be defined")
#endif

#endif
