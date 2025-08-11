TARGET=adaptive_autosar

for dir in ap_sm ap_ipchandler ap_katech ap_soa_roa ap_soa_wiper ap_soa_rearcurtain ap_subscriptionmanager ap_intelligent_wiper
do
  sudo rm -rf "$dir/$TARGET"
  ln -s ../$TARGET "$dir/$TARGET"
done
