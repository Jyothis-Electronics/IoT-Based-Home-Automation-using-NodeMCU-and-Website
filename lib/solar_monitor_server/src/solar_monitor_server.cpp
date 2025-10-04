#include "solar_monitor_server.h"
#include "config.h"

void SolarMonitorServer::send_html_header(WiFiClient &client) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println("Connection: close");
  client.println();
  client.println("<!DOCTYPE html>");
  client.println("<html lang=\"en\">");
  client.println("<head>");
  client.println("<meta charset=\"UTF-8\">");
  client.println("<meta name=\"viewport\" content=\"width=device-width, "
                 "initial-scale=1.0\">");
  client.println("<title>IoT Home Automation - Solar Monitor</title>");
  client.println("<link rel=\"icon\" href=\"data:,\">");
  client.println("<link rel=\"stylesheet\" href=\"https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.4.0/css/all.min.css\">");
}

void SolarMonitorServer::send_modern_css(WiFiClient &client) {
  client.println("<style>");
  client.println("* { margin: 0; padding: 0; box-sizing: border-box; }");
  client.println("body {");
  client.println(
      "  font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;");
  client.println(
      "  background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);");
  client.println("  min-height: 100vh;");
  client.println("  color: #333;");
  client.println("  display: flex;");
  client.println("  align-items: center;");
  client.println("  justify-content: center;");
  client.println("  padding: 20px;");
  client.println("}");

  client.println(".container {");
  client.println("  width: 100%;");
  client.println("  max-width: 800px;");
  client.println("  background: rgba(255, 255, 255, 0.95);");
  client.println("  border-radius: 20px;");
  client.println("  padding: 30px;");
  client.println("  box-shadow: 0 15px 35px rgba(0, 0, 0, 0.1);");
  client.println("  backdrop-filter: blur(10px);");
  client.println("}");

  client.println(".header {");
  client.println("  text-align: center;");
  client.println("  margin-bottom: 30px;");
  client.println("}");

  client.println("h1 {");
  client.println("  color: #2c3e50;");
  client.println("  font-size: 2.5em;");
  client.println("  margin-bottom: 10px;");
  client.println("  text-shadow: 2px 2px 4px rgba(0,0,0,0.1);");
  client.println("}");

  client.println(".ip-address {");
  client.println("  color: #7f8c8d;");
  client.println("  font-size: 1.1em;");
  client.println("  background: #ecf0f1;");
  client.println("  padding: 10px 20px;");
  client.println("  border-radius: 25px;");
  client.println("  display: inline-block;");
  client.println("  margin-bottom: 20px;");
  client.println("}");

  client.println(".relay-controls {");
  client.println("  display: grid;");
  client.println("  grid-template-columns: 1fr 1fr;");
  client.println("  gap: 20px;");
  client.println("  margin-bottom: 30px;");
  client.println("}");

  client.println(".relay-card {");
  client.println("  background: white;");
  client.println("  border-radius: 15px;");
  client.println("  padding: 25px;");
  client.println("  text-align: center;");
  client.println("  box-shadow: 0 8px 25px rgba(0, 0, 0, 0.1);");
  client.println("  transition: transform 0.3s ease, box-shadow 0.3s ease;");
  client.println("}");

  client.println(".relay-card:hover {");
  client.println("  transform: translateY(-5px);");
  client.println("  box-shadow: 0 12px 35px rgba(0, 0, 0, 0.15);");
  client.println("}");

  client.println(".relay-title {");
  client.println("  font-size: 1.3em;");
  client.println("  font-weight: bold;");
  client.println("  color: #2c3e50;");
  client.println("  margin-bottom: 15px;");
  client.println("}");

  client.println(".relay-status {");
  client.println("  font-size: 1.1em;");
  client.println("  margin-bottom: 20px;");
  client.println("  padding: 8px 16px;");
  client.println("  border-radius: 20px;");
  client.println("  display: inline-block;");
  client.println("  font-weight: bold;");
  client.println("}");

  client.println(".status-on {");
  client.println("  background: #d5e8d4;");
  client.println("  color: #27ae60;");
  client.println("  border: 2px solid #27ae60;");
  client.println("}");

  client.println(".status-off {");
  client.println("  background: #fadbd8;");
  client.println("  color: #e74c3c;");
  client.println("  border: 2px solid #e74c3c;");
  client.println("}");

  client.println(".relay-button {");
  client.println("  border: none;");
  client.println("  padding: 15px 30px;");
  client.println("  font-size: 1.1em;");
  client.println("  font-weight: bold;");
  client.println("  border-radius: 50px;");
  client.println("  cursor: pointer;");
  client.println("  transition: all 0.3s ease;");
  client.println("  text-transform: uppercase;");
  client.println("  letter-spacing: 1px;");
  client.println("  min-width: 120px;");
  client.println("}");

  client.println(".btn-on {");
  client.println("  background: linear-gradient(45deg, #27ae60, #2ecc71);");
  client.println("  color: white;");
  client.println("  box-shadow: 0 4px 15px rgba(46, 204, 113, 0.4);");
  client.println("}");

  client.println(".btn-off {");
  client.println("  background: linear-gradient(45deg, #e74c3c, #c0392b);");
  client.println("  color: white;");
  client.println("  box-shadow: 0 4px 15px rgba(231, 76, 60, 0.4);");
  client.println("}");

  client.println(".relay-button:hover {");
  client.println("  transform: translateY(-2px);");
  client.println("  box-shadow: 0 6px 20px rgba(0, 0, 0, 0.3);");
  client.println("}");

  client.println(".relay-button:active {");
  client.println("  transform: translateY(0);");
  client.println("}");

  client.println(".status-panel {");
  client.println("  background: white;");
  client.println("  border-radius: 15px;");
  client.println("  padding: 20px;");
  client.println("  box-shadow: 0 8px 25px rgba(0, 0, 0, 0.1);");
  client.println("  text-align: center;");
  client.println("}");

  client.println(".last-update {");
  client.println("  color: #7f8c8d;");
  client.println("  font-size: 0.9em;");
  client.println("  margin-top: 15px;");
  client.println("}");

  client.println(".loading {");
  client.println("  opacity: 0.6;");
  client.println("  pointer-events: none;");
  client.println("}");

  client.println("@media (max-width: 768px) {");
  client.println("  .relay-controls { grid-template-columns: 1fr; }");
  client.println("  .container { padding: 20px; margin: 10px; }");
  client.println("  h1 { font-size: 2em; }");
  client.println("  body { padding: 10px; }");
  client.println("}");

  client.println("</style>");
}

void SolarMonitorServer::send_javascript(WiFiClient &client) {
  client.println("<script>");
  client.println("let relay1State = false;");
  client.println("let relay2State = false;");
  client.println("let isLoading = false;");

  client.println("function toggleRelay(relayNum) {");
  client.println("  if (isLoading) return;");
  client.println("  isLoading = true;");
  client.println(
      "  document.querySelector('.container').classList.add('loading');");

  client.println(
      "  const newState = (relayNum === 1) ? !relay1State : !relay2State;");
  client.println(
      "  const url = `/data?relay${relayNum}=${newState ? 'on' : 'off'}`;");

  client.println("  fetch(url)");
  client.println("    .then(response => response.json())");
  client.println("    .then(data => {");
  client.println("      updateUI(data);");
  client.println("    })");
  client.println("    .catch(error => {");
  client.println("      console.error('Error:', error);");
  client.println("    })");
  client.println("    .finally(() => {");
  client.println("      isLoading = false;");
  client.println(
      "      "
      "document.querySelector('.container').classList.remove('loading');");
  client.println("    });");
  client.println("}");

  client.println("function updateUI(data) {");
  client.println("  relay1State = data.relay_1_state;");
  client.println("  relay2State = data.relay_2_state;");

  client.println(
      "  const relay1Status = document.getElementById('relay1-status');");
  client.println(
      "  const relay1Button = document.getElementById('relay1-button');");
  client.println(
      "  const relay2Status = document.getElementById('relay2-status');");
  client.println(
      "  const relay2Button = document.getElementById('relay2-button');");

  client.println("  relay1Status.textContent = relay1State ? 'ON' : 'OFF';");
  client.println("  relay1Status.className = 'relay-status ' + (relay1State ? "
                 "'status-on' : 'status-off');");
  client.println(
      "  relay1Button.textContent = relay1State ? 'Turn OFF' : 'Turn ON';");
  client.println("  relay1Button.className = 'relay-button ' + (relay1State ? "
                 "'btn-off' : 'btn-on');");

  client.println("  relay2Status.textContent = relay2State ? 'ON' : 'OFF';");
  client.println("  relay2Status.className = 'relay-status ' + (relay2State ? "
                 "'status-on' : 'status-off');");
  client.println(
      "  relay2Button.textContent = relay2State ? 'Turn OFF' : 'Turn ON';");
  client.println("  relay2Button.className = 'relay-button ' + (relay2State ? "
                 "'btn-off' : 'btn-on');");

  client.println("  document.getElementById('last-update').textContent = 'Last "
                 "updated: ' + new Date().toLocaleTimeString();");
  client.println("}");

  client.println("function refreshStatus() {");
  client.println("  fetch('/data')");
  client.println("    .then(response => response.json())");
  client.println("    .then(data => updateUI(data))");
  client.println("    .catch(error => console.error('Error:', error));");
  client.println("}");

  client.println("setInterval(refreshStatus, 5000);");
  client.println("window.onload = refreshStatus;");

  client.println("</script>");
}

void SolarMonitorServer::present_modern_website(WiFiClient &client,
                                                RelayStatus &relay_data) {
  send_html_header(client);
  send_modern_css(client);
  client.println("</head>");
  client.println("<body>");
  client.println("  <div class=\"container\">");
  client.println("    <div class=\"header\">");
  client.println("      <h1><i class=\"fa-solid fa-tower-cell\"></i> IoT Home Automation</h1>");
  client.println("      <div class=\"ip-address\"><i class=\"fa-solid fa-wifi\"></i> Device IP: " +
                 WiFi.localIP().toString() + "</div>");
  client.println("    </div>");

  client.println("    <div class=\"relay-controls\">");

  // Relay 1 Card
  client.println("      <div class=\"relay-card\">");
  client.println(
      "        <div class=\"relay-title\"><i class=\"fa-solid fa-lightbulb\"></i> Relay 1 - Light Control</div>");
  client.println("        <div id=\"relay1-status\" class=\"relay-status " +
                 String(relay_data.relay_1_state ? "status-on" : "status-off") +
                 "\">" + String(relay_data.relay_1_state ? "ON" : "OFF") +
                 "</div>");
  client.println("        <button id=\"relay1-button\" class=\"relay-button " +
                 String(relay_data.relay_1_state ? "btn-off" : "btn-on") +
                 "\" onclick=\"toggleRelay(1)\">" +
                 String(relay_data.relay_1_state ? "Turn OFF" : "Turn ON") +
                 "</button>");
  client.println("      </div>");

  // Relay 2 Card
  client.println("      <div class=\"relay-card\">");
  client.println(
      "        <div class=\"relay-title\"><i class=\"fa-solid fa-plug\"></i> Relay 2 - Power Control</div>");
  client.println("        <div id=\"relay2-status\" class=\"relay-status " +
                 String(relay_data.relay_2_state ? "status-on" : "status-off") +
                 "\">" + String(relay_data.relay_2_state ? "ON" : "OFF") +
                 "</div>");
  client.println("        <button id=\"relay2-button\" class=\"relay-button " +
                 String(relay_data.relay_2_state ? "btn-off" : "btn-on") +
                 "\" onclick=\"toggleRelay(2)\">" +
                 String(relay_data.relay_2_state ? "Turn OFF" : "Turn ON") +
                 "</button>");
  client.println("      </div>");

  client.println("    </div>");

  client.println("    <div class=\"status-panel\">");
  client.println("      <h3><i class=\"fa-solid fa-chart-line\"></i> System Status</h3>");
  client.println("      <p id=\"last-update\" class=\"last-update\">Last "
                 "updated: --:--:--</p>");
  client.println("    </div>");

  client.println("  </div>");

  send_javascript(client);

  client.println("</body>");
  client.println("</html>");
}

void SolarMonitorServer::present_website(WiFiClient &client,
                                         RelayStatus &relay_data) {
  present_modern_website(client, relay_data);
}
void SolarMonitorServer::update_json_response(WiFiClient &client,
                                              RelayStatus &relay_data) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: application/json");
  client.println("Connection: close");
  client.println();

  client.print("{");
  client.print("\"relay_1_state\":");
  client.print(relay_data.relay_1_state ? "true" : "false");
  client.print(",");
  client.print("\"relay_2_state\":");
  client.print(relay_data.relay_2_state ? "true" : "false");
  client.print(",");
  client.print("\"timestamp\":");
  client.print(millis());
  client.println("}");
}
