<!DOCTYPE html>
<html>
    <head>
        <title>Arduino Ajax LED Button Control</title>
        <script>
        strLED1 = "";
        strLED2 = "";
        var LED2_state = 0;
        function GetArduinoIO()
        {
            nocache = "&nocache=" + Math.random() * 1000000;
            var request = new XMLHttpRequest();
            request.onreadystatechange = function()
            {
                if (this.readyState == 4) {
                    if (this.status == 200) {
                        if (this.responseXML != null) {
                            var count;
                            // LED 1
                            if (this.responseXML.getElementsByTagName('LED')[0].childNodes[0].nodeValue === "checked") {
                                document.LED_form.LED1.checked = true;
                            }
                            else {
                                document.LED_form.LED1.checked = false;
                            }
                            // LED 2
                            if (this.responseXML.getElementsByTagName('LED')[1].childNodes[0].nodeValue === "on") {
                                document.getElementById("LED2").innerHTML = "LED 2 is ON (D7)";
                                LED2_state = 1;
                            }
                            else {
                                document.getElementById("LED2").innerHTML = "LED 2 is OFF (D7)";
                                LED2_state = 0;
                            }
                        }
                    }
                }
            }
            // send HTTP GET request with LEDs to switch on/off if any
            request.open("GET", "ajax_inputs" + strLED1 + strLED2 + nocache, true);
            request.send(null);
            setTimeout('GetArduinoIO()', 1000);
            strLED1 = "";
            strLED2 = "";
        }
        // service LEDs when checkbox checked/unchecked
        function GetCheck()
        {
            if (LED_form.LED1.checked) {
                strLED1 = "&LED1=1";
            }
            else {
                strLED1 = "&LED1=0";
            }
        }
        function GetButton1()
        {
            if (LED2_state === 1) {
                LED2_state = 0;
                strLED2 = "&LED2=0";
            }
            else {
                LED2_state = 1;
                strLED2 = "&LED2=1";
            }
        }
    </script>
    <style>
        .IO_box {
            float: left;
            margin: 0 20px 20px 0;
            border: 1px solid blue;
            padding: 0 5px 0 5px;
            width: 120px;
        }
        h1 {
            font-size: 120%;
            color: blue;
            margin: 0 0 10px 0;
        }
        h2 {
            font-size: 85%;
            color: #5734E6;
            margin: 5px 0 5px 0;
        }
        p, form, button {
            font-size: 80%;
            color: #252525;
        }
        .small_text {
            font-size: 70%;
            color: #737373;
        }
    </style>
    </head>
    <body onload="GetArduinoIO()">
        <h1>Arduino Ajax LED Button Control</h1>
        <div class="IO_box">
            <h2>LED Using Checkbox</h2>
            <form id="check_LEDs" name="LED_form">
                <input type="checkbox" name="LED1" value="0" onclick="GetCheck()" />LED 1 (D6)<br /><br />
            </form>
        </div>
        <div class="IO_box">
            <h2>LED Using Button</h2>
            <button type="button" id="LED2" onclick="GetButton1()">LED 2 is OFF (D7)</button><br /><br />
        </div>
    </body>
</html>