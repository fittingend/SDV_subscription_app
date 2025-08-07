
echo "📦 Updating adaptive_autosar..."
cd adaptive_autosar && git pull || echo "❌ adaptive_autosar pull failed"
cd ..

echo "📦 Updating ap_sm..."
cd ap_sm && git pull || echo "❌ ap_sm pull failed"
cd ..

echo "📦 Updating ap_ipchandler..."
cd ap_ipchandler && git pull || echo "❌ ap_ipchandler pull failed"
cd ..

echo "✅ All repositories updated."
