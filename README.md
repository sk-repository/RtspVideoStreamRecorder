# RtspVideoStreamRecorder


## Dependencies
RtspVideoStreamRecorder is based on [FFMPEG](https://ffmpeg.org/). Application needs Qt 5.12.1 librarys. 

RtspVideoStreamRecorder was install and tested in the following systems:

| OS           | ffmpeg |
|--------------|--------|
| Ubuntu 16.04 | 4.1.3  |
| Ubuntu 18.04 | 3.4.6  | 

## Install
### Manual run
1. Copy QtLibs to: /opt/Qt5.12.1/5.12.1/gcc_64/lib/
2. Install ffmpeg:
```shell
sudo apt-get install ffmpeg
```
3. Copy RtspVideoStreamRecorder file to: /root/RVSR/
4. Edit "config.json" in: /root/RVSR/
5. Run application by ./start-rvsr.sh

### Run as service
1. Copy rvsr file to /etc/init.d/
2. chmod+x
3. update-rc.d rvsr defaults

## Configuration example
```shell
{
	"GeneralSettings": {
		"SegmentLenghtInMins": 5,
		"RecordsPath": "/home/sk/Dokumenty/rec/",
		"ArchivingInDays": 1
	},
	"Cameras": [
		"rtsp://admin:Admin123456@192.168.204.26:2101/Streaming/Channels/2",
		"rtsp://admin:admin@10.1.1.246:8554/CH002.sdp"
	]
}
```
## Algorithm

---------------         ----------------------
|    START    |-------->| READ "config.json" |
---------------         ----------------------





