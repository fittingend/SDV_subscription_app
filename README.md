# SDV_subscription_app

### 폴더 구조
eevp_main_machine/  
├── ap_app/             \# 모비스 앱 모음  
├── subscription_app/   \# 구독 서비스 앱 모음  
└── adaptive_autosar/   \# Adaptive Autosar 모음  


### 모비스 앱 업데이트

외부 환경에서  

cd src/eevp_main_machine  
./hd_update.sh

### 구독 앱 심볼릭링크 생성

도커 환경에서  

cd src/eevp_main_machine  
./sub_symbollink.sh

### build.sh 사용법

build.sh 내 modules 수정

modules="  
ap_sm|-c -p|ap_app  
ap_ipchandler||ap_app  
ap_soa_wiper||ap_app  
\#ap_intelligent_wiper||subscription_app  
ap_katech||subscription_app  
"

(원하는 앱 명칭)||(ap_app or subscription_app) 추가하거나 \#주석처리

build.sh 사용  

cd src/eevp_main_machine  
./hd_update.sh

### EM 실행용 test.sh 사용법
sh $PWD/test.sh


