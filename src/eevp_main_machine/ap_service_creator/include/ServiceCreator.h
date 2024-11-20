#ifndef __SERVICE_CREATOR_H__
#define __SERVICE_CREATOR_H__

#include <csignal>
#include <thread>
#include <ctime>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <fstream>
#include <iostream>
#include <curl/curl.h>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <ara/log/logger.h>

#include <json.hpp>

#include "skeleton/WiperSkeletonImpl.h"
#include "skeleton/TMoodLampSkeletonImpl.h"
#include "skeleton/BmsInfoSkeletonImpl.h"
#include "proxy/MsgInfoProxyImpl.h"
#include "skeleton/AccrPedalSkeletonImpl.h"
#include "skeleton/EnvMonitorSkeletonImpl.h"
#include "skeleton/GearSkeletonImpl.h"
#include "skeleton/BrakePedalSkeletonImpl.h"
#include "skeleton/VehSpdSkeletonImpl.h"
#include "skeleton/SnsrUssSkeletonImpl.h"
#include "skeleton/LotteSkeletonImpl.h"
#include "skeleton/SESLServiceSkeletonImpl.h"

#define BUF_SIZE 1024
using namespace ara::core;
using json = nlohmann::json;
using namespace bms::output;

namespace eevp
{
    namespace simulation
    {
        class ServiceCreator
        {
        public:
            /// @brief Constructor
            ServiceCreator();
            /// @brief Destructor
            ~ServiceCreator();

            /// @brief Start S/W Component
            bool Start();
            /// @brief Run S/W Component
            void Run();
            /// @brief Terminate S/W Component
            void Terminate();

            // IWiperListener
            void stopWiping();
            void startWiping();
            void setWipingInterval(const std::uint16_t &wipingInterval);
            void setWipingLevel(const eevp::simulation::BCM_WipingLevel &wipingLevel);

            // WiperVar
            eevp::simulation::BCM_WipingLevel wipingLevelReceive;
            std::uint16_t wipingIntervalReceive;
            eevp::simulation::BCM_WipingLevel wipingLevelSend;
            std::uint16_t wipingIntervalSend;
            static std::string wiperLevel[];

            // ITMoodLampListener
            void RequestMImSetBrightness(const std::uint16_t &Brightness);
            void RequestMImSetMode(const lmp::mode::SoaMImMoodeMode &mood);
            void RequestMImSetRGBColor(const std::uint8_t &ColorIndex);

            // TMoodLampVar
            std::uint16_t BrightnessSend;
            lmp::mode::SoaMImMoodeMode moodSend;
            std::uint8_t ColorIndexSend;

            // BmsInfoSrv
            void notifyBmsInfo(bms::input::InputData &info);

            // BmsInfoVar
            bms::input::InputData bmsInfo;

            // IMsgInfoListener
            void notifyMsgInfo(const bms::output::OutputData &output);

            // IAccrPedalListener
            void notifyAccrPedal(eevp::simulation::type::VCS_AccrPedal &accrPedal);

            // AccrPedalVar
            eevp::simulation::type::VCS_AccrPedal accrPedal;

            // IEnvMonitorListener
            void notifyHumidity(eevp::simulation::type::TMS_EnvZoneHumidityAry &envZoneHumidityAry);

            // EnvMonitorVar
            eevp::simulation::type::TMS_EnvZoneHumidityAry envZoneHumidityAry;

            // IGearListener
            void notifyGear(eevp::simulation::type::VCS_Gear &gear);

            // GearVar
            eevp::simulation::type::VCS_Gear gear;

            // IBrakePedalListener
            void notifyPosn(eevp::simulation::type::VCS_BrakePosn &brakePosn);
            void notifyBrakeSwitch(eevp::simulation::type::VCS_BrakeSwitch &brakeSwitch);

            // BrakePedalVar
            eevp::simulation::type::VCS_BrakePosn brakePosn;
            eevp::simulation::type::VCS_BrakeSwitch brakeSwitch;

            // IVehSpdListener
            void notifyVehSpd(eevp::simulation::type::VCS_VehSpd &vehSpd);

            // VehSpdVar
            eevp::simulation::type::VCS_VehSpd vehSpd;

            // ISnsrUssListener
            void ntfSonarInfo(eevp::simulation::type::USSSonarInfo &ussSonarInfo);

            // SnsrUssVar
            eevp::simulation::type::USSSonarInfo ussSonarInfo;

            // ILotteListener
            void NotifyDmsCurr(lotte::type::DmsGzDtctn &dmsGzDtctn);
            void NotifyDmsStatus(bool &result);
            void NotifySmartFilmCurr(lotte::type::SideTransparency &result);
            void NotifySmartFilmStatus(bool &result);
            void SmartFilmControl(const std::int32_t &windowLoc, const std::int32_t &transparence);

            // LotteVar
            std::int32_t windowLocSend;
            std::int32_t transparenceSend;
            bool dmsStatus = true;
            bool smartFilmStatus = true;

            // ISESLServiceListener
            void SESL_Receive(ara::SESL::Vehicle_Data &Receive_Argument);
            void SESL_Send(const ara::SESL::Vehicle_Data &Send_Argument);

            // SESLVar
            ara::SESL::Vehicle_Data vehicle_Data_receive;
            ara::SESL::Vehicle_Data vehicle_Data_send;

            // Thread
            void poolingFieldUpdate();

            static pthread_t thread_socket_recv;
            static pthread_t thread_socket_send;
            std::thread *updateThread;
            std::atomic<bool> uThreadRunning;
            static void *socket_recv(void *inst);
            static void *socket_send(void *inst);

            // json 데이터 추출
            void extractWiperData(const json &wiperData);
            void extractBatteryData(const json &bmsData);
            void extractAccrPedalData(const json &accrPedalData);
            void extractEnvMonitorData(const json &envMonitorData);
            void extractGearData(const json &gearData);
            void extractBrakePedalData(const json &brakePedalData);
            void extractVehSpdData(const json &vehSpdData);
            void extractSnsrUssData(const json &sonarData);
            void extractLotteData(const json &lotteData);
            void extractSESLData(const json &seslData);

        private:
            static void SignalHandler(std::int32_t signal);

            /// @brief set Running State
            bool setRunningState();

            bool startSocketClient();

            bool startServiceCreatorStub();

            bool startMsgInfoProxy();

            bool initialize();

            static std::atomic_bool mRunning;
            ara::log::Logger &mLogger;

            std::shared_ptr<eevp::simulation::WiperSkeletonImpl> wiperSkeletonImpl;
            std::shared_ptr<eevp::simulation::TEevpControlSoaMImSkeletonImpl> tEevpControlSoaMImSkeletonImpl;
            std::shared_ptr<eevp::simulation::BmsInfoSkeletonImpl> bmsInfoSkeletonImpl;
            std::shared_ptr<eevp::simulation::MsgInfoProxyImpl> msgInfoProxyImpl;
            std::shared_ptr<eevp::simulation::AccrPedalSkeletonImpl> accrPedalSkeletonImpl;
            std::shared_ptr<eevp::simulation::EnvMonitorSkeletonImpl> envMonitorSkeletonImpl;
            std::shared_ptr<eevp::simulation::GearSkeletonImpl> gearSkeletonImpl;
            std::shared_ptr<eevp::simulation::BrakePedalSkeletonImpl> brakePedalSkeletonImpl;
            std::shared_ptr<eevp::simulation::VehSpdSkeletonImpl> vehSpdSkeletonImpl;
            std::shared_ptr<eevp::simulation::SnsrUssSkeletonImpl> snsrUssSkeletonImpl;
            std::shared_ptr<eevp::simulation::LotteSkeletonImpl> lotteSkeletonImpl;
            std::shared_ptr<eevp::simulation::SESLServiceSkeletonImpl> seslServiceSkeletonImpl;

            void getWiperRecv();
            void getWiperSend();

            std::vector<std::string> parseData;

            std::mutex mtx;             // 데이터 보호를 위한 뮤텍스
            std::condition_variable cv; // 값 변경을 알리기 위한 조건 변수

            // json 라이브러리
            json prepareData();

        };

    } // namespace monitoring
} // namespace eevp

#endif // __SERVICE_CREATOR_H__