# OTA-Client
1. Install and run Hawkbit Server
2. Configure the OTA-Client
3. Create an Update Campaign
4. Run the client on the target
5. Known limitations


# 1. Install and run Hawkbit Server

​	Eclipse hawkBit™ is a domain independent back-end framework for rolling out software updates to constrained edge devices as well as more powerful controllers and gateways connected to IP based networking infrastructure.

​	HawkBit offers a direct device integration via HTTP or a device management federation API which allows to connect devices with different protocol adapter. Users can make use of the graphical user interface and other service can interact with hawkBit through the RESTful management API.

​	HawkBit supports an easy and flexible rollout management which allows you to update a large amount of devices in separated groups. A software update does not always contain only a single file. The hawkBit meta model allows you to configure your files in virtual software and distribution packages.

#### Hawkbit Installation

We will assume you have two machines connected on an IP network:

- A development machine running a standard Linux distribution. We will assume that this machine has the *192.168.7.11* IP address. This machine must have Java 8 (Both OpenJDK and Oracle Java 1.8 work), Maven and rabbitmq-server installed.
- A raspberrypi or a virtual machine running the AUTOSAR Demonstrator.

We will fetch Hawkbit from its GitHub repository.

```
$ git clone https://github.com/eclipse/hawkbit
$ cd hawkbit
```

The tests were done using the version 0.2.0M4. We need to manually select a slightly older version of Hawkbit.

```
$ git checkout 0.2.0M4
```

We can now compile Hawkbit using Maven.

```
$ mvn clean install
```

And run the generated Hawkbit Server:

```
$ java -jar ./hawkbit-runtime/hawkbit-update-server/target/hawkbit-update-server-0.2.0-SNAPSHOT.jar
```

#### Accessing the Hawkbit panel

​Hawkbit offers two mechanisms for artifacts management: the Management UI and the Management API. We will detail the usage of the Management UI here.

You can access the Management UI from a Web Browser on the development machine by opening the following URL: [http://localhost:8080](http://localhost:8080/)

The default credentials are:

- username: *admin*
- password: *admin*

To change those logins, you need to modify `hawkbit-runtime/hawkbit-update-server/src/main/resources/application.properties` and recompile Hawkbit using `mvn clean install`.



# 2. Configure the OTA-Client

The client's configuration parameters are present in the file `config.ini`. This file has the following structure:

```
  [client]
  hawkbit_server            = 192.168.7.11:8080
  ssl                       = false
  ssl_verify                = false
  tenant_id                 = DEFAULT
  target_name               = ota-client
  auth_token                = bhVahL1Il1shie2aj2poojeChee6ahShu
  gateway_token             = bhVahL1Il1shie2aj2poojeChee6ahShu
  download_location         = /tmp
  retry_wait                = 60
  connect_timeout           = 20
  timeout                   = 60
  log_level                 = debug

  [device]
  product                   = APD
  model                     = Demonstrator
  serialnumber              = 8922673153
  hw_revision               = 2
  key1                      = value
  key2                      = value
```

All key/values under [device] group are sent to hawkBit as data (attributes). The attributes in HawkBit can be used in target filters.



# 2. Create an Update Campaign

#### Upload

- Go to the **Upload** tab from the left selector
- Create a Software Module of type "OS" named test-campaign of version 1.0 and then click on it
- Upload Procedure: Use the "Upload file" button to select the vehicle package zip for the campaign then press the "Process" button to validate the upload
- Repeat the Upload Procedure for every SW package zip.

*Note:* Hawkbit offers "Management APIs" that can potentially automatize those steps.

#### Distribution Management

- Go to the **Distributions Management** tab from the left selector
- Create a Distribution of type "OS with app(s)", named AAP of version 1.0
- Drag and drop the test-campaign on the right pane onto the AAP distribution on the left pane
- Click the actions button and apply the changes

#### Target Filters

- Go to the **Target Filters** tab from the left selector
- Create a new filter named "Default filter" and use a generic filter such as “name==*"

#### Rollout

- Before creating a rollout, make sure the OTA Client has already identified itself to the server. Otherwise a rollout can't be created. Go to **Deployment** tab
  to check if OTA Client has been identified. The target can also be created manually by using ID "ota-client".
- Go to the **Rollout** tab from the left selector
- Create a new rollout campaign named "AAP 1.0 Deployment". Select the AAP distribution set, the default filter and enter 1 in the "Number of groups" field. You should see stats of deployment appearing
- Press the "Play" icon on the right side of your rollout campaign to activate the deployment

#### Applying the update

At this point, you can either wait for a while, so that OTA Client polls for updates and finds the new deployment campaign. You should find detailed information on the download process in the output of OTA Client.

When the update is applied, you can also check the Hawkbit Management UI and see the status of your rollout campaign changed.

# 3. Known limitations

This client treats the first received file as the vehicle package, all other files as SW packages. After successful download the client starts the update campaign.
After execution of campaign a feedback is send to hawkbit server.

------

#### References

[1]: https://www.eclipse.org/hawkbit/
[2]: https://pelux.io/software-factory/PELUX-3.0/chapters/architecture/subsystems/SOTA/getting-started-SOTA.html

