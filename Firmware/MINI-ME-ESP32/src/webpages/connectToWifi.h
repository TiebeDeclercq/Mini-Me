const char* html_page = R"(
    <!DOCTYPE html>
    <html>
    <head>
        <title>WiFi Instellingen</title>
        <style>
            body { 
                font-family: Arial; 
                padding: 20px;
                max-width: 500px;
                margin: 0 auto;
                text-align: center;
            }
            .input-group {
                margin: 15px 0;
            }
            input {
                padding: 8px;
                width: 80%;
                margin: 5px 0;
            }
            button {
                background-color: #4CAF50;
                color: white;
                padding: 10px 20px;
                border: none;
                border-radius: 4px;
                cursor: pointer;
            }
            button:hover {
                background-color: #45a049;
            }
        </style>
    </head>
    <body>
        <h1>WiFi Instellingen</h1>
        <form action="/save" method="POST">
            <div class="input-group">
                <label for="ssid">Netwerknaam (SSID):</label><br>
                <input type="text" id="ssid" name="ssid">
            </div>
            <div class="input-group">
                <label for="password">Wachtwoord:</label><br>
                <input type="password" id="password" name="password">
            </div>
            <button type="submit">Verbinden</button>
        </form>
    </body>
    </html>
    )";