echo "📦 Updating adaptive_autosar..."
cd adaptive_autosar && git pull || echo "❌ adaptive_autosar pull failed"
cd ..

echo "📦 Updating ap_sm..."
cd ap_sm && git pull || echo "❌ ap_sm pull failed"
cd ..

echo "📦 Updating ap_ipchandler..."
cd ap_ipchandler && git pull || echo "❌ ap_ipchandler pull failed"
cd ..

echo "📦 Updating ap_soa_roa..."
cd ap_soa_roa && git pull || echo "❌ ap_soa_roa pull failed"
cd ..

echo "📦 Updating ap_soa_wiper..."
cd ap_soa_wiper && git pull || echo "❌ ap_soa_wiper pull failed"
cd ..

echo "📦 Updating ap_soa_rearcurtain..."
cd ap_soa_rearcurtain && git pull || echo "❌ ap_soa_rearcurtain pull failed"
cd ..

echo "📦 Updating ap_subscriptionmanager..."
cd ap_subscriptionmanager && git pull || echo "❌ ap_subscriptionmanager pull failed"
cd ..

echo "✅ All repositories updated."

