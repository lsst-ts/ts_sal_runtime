
package org.lsst.sal;

import org.opensplice.dds.dcps.TypeSupportImpl;
import DDS.*;
import DDS.STATUS_MASK_NONE; 
import DDS.DOMAIN_ID_DEFAULT;
import DDS.DATAREADER_QOS_USE_TOPIC_QOS;
import DDS.DataReader;
import DDS.DataWriter;
import DDS.DataWriterQosHolder;
import DDS.DomainParticipant;
import DDS.DomainParticipantFactory;
import DDS.DurabilityQosPolicyKind;
import DDS.PARTICIPANT_QOS_DEFAULT;
import DDS.Publisher;
import DDS.PublisherQosHolder;
import DDS.ReliabilityQosPolicyKind;
import DDS.Subscriber;
import DDS.SubscriberQosHolder;
import DDS.Topic;
import DDS.TopicQosHolder;
import DDS.DurabilityQosPolicyKind;
import DDS.HANDLE_NIL;
import DDS.ANY_INSTANCE_STATE;
import DDS.ANY_SAMPLE_STATE;
import DDS.ANY_VIEW_STATE;
import DDS.DataReader;
import DDS.LENGTH_UNLIMITED;
import DDS.SampleInfoSeqHolder;
import org.lsst.sal.salActor;
import java.util.Random;

import camera.*;
// INSERT SAL IMPORTS

public class SAL_camera {

	private DomainParticipantFactory dpf;
	private DomainParticipant participant;
	private Topic topic;
        private Topic topic2;
        private ContentFilteredTopic filteredtopic;
        private ContentFilteredTopic filteredtopic2;
	private TopicQosHolder topicQos = new TopicQosHolder();
	private TopicQosHolder topicQos2 = new TopicQosHolder();
	private PublisherQosHolder pubQos = new PublisherQosHolder();
	private SubscriberQosHolder subQos = new SubscriberQosHolder();

	private DataWriterQosHolder WQosH = new DataWriterQosHolder();

	private Publisher publisher;
	private DataWriter writer;
	private DataWriter writer2;

	private Subscriber subscriber;
	private DataReader reader;
	private DataReader reader2;

	private String typeName;
	private String typeName2;
	private String partitionName;
        private Boolean hasReader;
        private Boolean hasWriter;
        private Boolean hasEventReader;
        private Boolean hasEventWriter;
        private Boolean hasProcessor;
        private Boolean hasCommand;
        private int debugLevel;
        private int sndSeqNum;
        private int rcvSeqNum;
        private int rcvOrigin;
        private short subsystemID;
        private long origin;
        private String domainName;
        private int lastActor_telemetry;
        private int lastActor_command;
        private int lastActor_event;

        salActor[] sal = new salActor[SAL__ACTORS_MAXCOUNT];

	public static final int SAL__camera_CCS_ACTOR = 0;
	public static final int SAL__camera_Cluster_Encoder_ACTOR = 1;
	public static final int SAL__camera_Cold_ACTOR = 2;
	public static final int SAL__camera_Cryo_ACTOR = 3;
	public static final int SAL__camera_Filter_ACTOR = 4;
	public static final int SAL__camera_GAS_ACTOR = 5;
	public static final int SAL__camera_GDS_ACTOR = 6;
	public static final int SAL__camera_PCMS_ACTOR = 7;
	public static final int SAL__camera_Prot_ACTOR = 8;
	public static final int SAL__camera_Purge_ACTOR = 9;
	public static final int SAL__camera_SAS_ACTOR = 10;
	public static final int SAL__camera_SDS_ACTOR = 11;
	public static final int SAL__camera_Shutter_ACTOR = 12;
	public static final int SAL__camera_WAS_ACTOR = 13;
	public static final int SAL__camera_WDS_ACTOR = 14;
	public static final int SAL__camera_ackcmd_ACTOR = 15;
	public static final int SAL__camera_command_ACTOR = 16;
	public static final int SAL__camera_command_SetValue_ACTOR = 17;
	public static final int SAL__camera_command_abort_ACTOR = 18;
	public static final int SAL__camera_command_configure_ACTOR = 19;
	public static final int SAL__camera_command_disable_ACTOR = 20;
	public static final int SAL__camera_command_enable_ACTOR = 21;
	public static final int SAL__camera_command_enterControl_ACTOR = 22;
	public static final int SAL__camera_command_exitControl_ACTOR = 23;
	public static final int SAL__camera_command_initGuiders_ACTOR = 24;
	public static final int SAL__camera_command_initImage_ACTOR = 25;
	public static final int SAL__camera_command_setFilter_ACTOR = 26;
	public static final int SAL__camera_command_standby_ACTOR = 27;
	public static final int SAL__camera_command_start_ACTOR = 28;
	public static final int SAL__camera_command_stop_ACTOR = 29;
	public static final int SAL__camera_command_takeImages_ACTOR = 30;
	public static final int SAL__camera_logevent_ACTOR = 31;
	public static final int SAL__camera_logevent_AppliedSettingsMatchStart_ACTOR = 32;
	public static final int SAL__camera_logevent_ErrorCode_ACTOR = 33;
	public static final int SAL__camera_logevent_SettingVersions_ACTOR = 34;
	public static final int SAL__camera_logevent_SummaryState_ACTOR = 35;
	public static final int SAL__camera_logevent_ccsConfigured_ACTOR = 36;
	public static final int SAL__camera_logevent_endInitializeGuider_ACTOR = 37;
	public static final int SAL__camera_logevent_endInitializeImage_ACTOR = 38;
	public static final int SAL__camera_logevent_endLoadFilter_ACTOR = 39;
	public static final int SAL__camera_logevent_endReadout_ACTOR = 40;
	public static final int SAL__camera_logevent_endRotateCarousel_ACTOR = 41;
	public static final int SAL__camera_logevent_endSetFilter_ACTOR = 42;
	public static final int SAL__camera_logevent_endShutterClose_ACTOR = 43;
	public static final int SAL__camera_logevent_endShutterOpen_ACTOR = 44;
	public static final int SAL__camera_logevent_endTakeImage_ACTOR = 45;
	public static final int SAL__camera_logevent_endUnloadFilter_ACTOR = 46;
	public static final int SAL__camera_logevent_notReadyToTakeImage_ACTOR = 47;
	public static final int SAL__camera_logevent_prepareToTakeImage_ACTOR = 48;
	public static final int SAL__camera_logevent_readyToTakeImage_ACTOR = 49;
	public static final int SAL__camera_logevent_startIntegration_ACTOR = 50;
	public static final int SAL__camera_logevent_startLoadFilter_ACTOR = 51;
	public static final int SAL__camera_logevent_startReadout_ACTOR = 52;
	public static final int SAL__camera_logevent_startRotateCarousel_ACTOR = 53;
	public static final int SAL__camera_logevent_startSetFilter_ACTOR = 54;
	public static final int SAL__camera_logevent_startShutterClose_ACTOR = 55;
	public static final int SAL__camera_logevent_startShutterOpen_ACTOR = 56;
	public static final int SAL__camera_logevent_startUnloadFilter_ACTOR = 57;
	public static final int SAL__ACTORS_MAXCOUNT = 58;

	public void initSalActors ()
	{

		sal[0]=new salActor();
		sal[0].topicName="camera_CCS";
		sal[1]=new salActor();
		sal[1].topicName="camera_Cluster_Encoder";
		sal[2]=new salActor();
		sal[2].topicName="camera_Cold";
		sal[3]=new salActor();
		sal[3].topicName="camera_Cryo";
		sal[4]=new salActor();
		sal[4].topicName="camera_Filter";
		sal[5]=new salActor();
		sal[5].topicName="camera_GAS";
		sal[6]=new salActor();
		sal[6].topicName="camera_GDS";
		sal[7]=new salActor();
		sal[7].topicName="camera_PCMS";
		sal[8]=new salActor();
		sal[8].topicName="camera_Prot";
		sal[9]=new salActor();
		sal[9].topicName="camera_Purge";
		sal[10]=new salActor();
		sal[10].topicName="camera_SAS";
		sal[11]=new salActor();
		sal[11].topicName="camera_SDS";
		sal[12]=new salActor();
		sal[12].topicName="camera_Shutter";
		sal[13]=new salActor();
		sal[13].topicName="camera_WAS";
		sal[14]=new salActor();
		sal[14].topicName="camera_WDS";
		sal[15]=new salActor();
		sal[15].topicName="camera_ackcmd";
		sal[16]=new salActor();
		sal[16].topicName="camera_command";
		sal[17]=new salActor();
		sal[17].topicName="camera_command_SetValue";
		sal[18]=new salActor();
		sal[18].topicName="camera_command_abort";
		sal[19]=new salActor();
		sal[19].topicName="camera_command_configure";
		sal[20]=new salActor();
		sal[20].topicName="camera_command_disable";
		sal[21]=new salActor();
		sal[21].topicName="camera_command_enable";
		sal[22]=new salActor();
		sal[22].topicName="camera_command_enterControl";
		sal[23]=new salActor();
		sal[23].topicName="camera_command_exitControl";
		sal[24]=new salActor();
		sal[24].topicName="camera_command_initGuiders";
		sal[25]=new salActor();
		sal[25].topicName="camera_command_initImage";
		sal[26]=new salActor();
		sal[26].topicName="camera_command_setFilter";
		sal[27]=new salActor();
		sal[27].topicName="camera_command_standby";
		sal[28]=new salActor();
		sal[28].topicName="camera_command_start";
		sal[29]=new salActor();
		sal[29].topicName="camera_command_stop";
		sal[30]=new salActor();
		sal[30].topicName="camera_command_takeImages";
		sal[31]=new salActor();
		sal[31].topicName="camera_logevent";
		sal[32]=new salActor();
		sal[32].topicName="camera_logevent_AppliedSettingsMatchStart";
		sal[33]=new salActor();
		sal[33].topicName="camera_logevent_ErrorCode";
		sal[34]=new salActor();
		sal[34].topicName="camera_logevent_SettingVersions";
		sal[35]=new salActor();
		sal[35].topicName="camera_logevent_SummaryState";
		sal[36]=new salActor();
		sal[36].topicName="camera_logevent_ccsConfigured";
		sal[37]=new salActor();
		sal[37].topicName="camera_logevent_endInitializeGuider";
		sal[38]=new salActor();
		sal[38].topicName="camera_logevent_endInitializeImage";
		sal[39]=new salActor();
		sal[39].topicName="camera_logevent_endLoadFilter";
		sal[40]=new salActor();
		sal[40].topicName="camera_logevent_endReadout";
		sal[41]=new salActor();
		sal[41].topicName="camera_logevent_endRotateCarousel";
		sal[42]=new salActor();
		sal[42].topicName="camera_logevent_endSetFilter";
		sal[43]=new salActor();
		sal[43].topicName="camera_logevent_endShutterClose";
		sal[44]=new salActor();
		sal[44].topicName="camera_logevent_endShutterOpen";
		sal[45]=new salActor();
		sal[45].topicName="camera_logevent_endTakeImage";
		sal[46]=new salActor();
		sal[46].topicName="camera_logevent_endUnloadFilter";
		sal[47]=new salActor();
		sal[47].topicName="camera_logevent_notReadyToTakeImage";
		sal[48]=new salActor();
		sal[48].topicName="camera_logevent_prepareToTakeImage";
		sal[49]=new salActor();
		sal[49].topicName="camera_logevent_readyToTakeImage";
		sal[50]=new salActor();
		sal[50].topicName="camera_logevent_startIntegration";
		sal[51]=new salActor();
		sal[51].topicName="camera_logevent_startLoadFilter";
		sal[52]=new salActor();
		sal[52].topicName="camera_logevent_startReadout";
		sal[53]=new salActor();
		sal[53].topicName="camera_logevent_startRotateCarousel";
		sal[54]=new salActor();
		sal[54].topicName="camera_logevent_startSetFilter";
		sal[55]=new salActor();
		sal[55].topicName="camera_logevent_startShutterClose";
		sal[56]=new salActor();
		sal[56].topicName="camera_logevent_startShutterOpen";
		sal[57]=new salActor();
		sal[57].topicName="camera_logevent_startUnloadFilter";

	}
        public int salTypeSupport(String topicName) {
		String[] parts = topicName.split("_");
                if ("camera".equals(parts[0]) ) {

                    if ( "camera_CCS".equals(topicName) ) {
			CCSTypeSupport CCSTS = new CCSTypeSupport();
			registerType(CCSTS);
                        return SAL__OK;
		    }

                    if ( "camera_Cluster_Encoder".equals(topicName) ) {
			Cluster_EncoderTypeSupport Cluster_EncoderTS = new Cluster_EncoderTypeSupport();
			registerType(Cluster_EncoderTS);
                        return SAL__OK;
		    }

                    if ( "camera_Cold".equals(topicName) ) {
			ColdTypeSupport ColdTS = new ColdTypeSupport();
			registerType(ColdTS);
                        return SAL__OK;
		    }

                    if ( "camera_Cryo".equals(topicName) ) {
			CryoTypeSupport CryoTS = new CryoTypeSupport();
			registerType(CryoTS);
                        return SAL__OK;
		    }

                    if ( "camera_Filter".equals(topicName) ) {
			FilterTypeSupport FilterTS = new FilterTypeSupport();
			registerType(FilterTS);
                        return SAL__OK;
		    }

                    if ( "camera_GAS".equals(topicName) ) {
			GASTypeSupport GASTS = new GASTypeSupport();
			registerType(GASTS);
                        return SAL__OK;
		    }

                    if ( "camera_GDS".equals(topicName) ) {
			GDSTypeSupport GDSTS = new GDSTypeSupport();
			registerType(GDSTS);
                        return SAL__OK;
		    }

                    if ( "camera_PCMS".equals(topicName) ) {
			PCMSTypeSupport PCMSTS = new PCMSTypeSupport();
			registerType(PCMSTS);
                        return SAL__OK;
		    }

                    if ( "camera_Prot".equals(topicName) ) {
			ProtTypeSupport ProtTS = new ProtTypeSupport();
			registerType(ProtTS);
                        return SAL__OK;
		    }

                    if ( "camera_Purge".equals(topicName) ) {
			PurgeTypeSupport PurgeTS = new PurgeTypeSupport();
			registerType(PurgeTS);
                        return SAL__OK;
		    }

                    if ( "camera_SAS".equals(topicName) ) {
			SASTypeSupport SASTS = new SASTypeSupport();
			registerType(SASTS);
                        return SAL__OK;
		    }

                    if ( "camera_SDS".equals(topicName) ) {
			SDSTypeSupport SDSTS = new SDSTypeSupport();
			registerType(SDSTS);
                        return SAL__OK;
		    }

                    if ( "camera_Shutter".equals(topicName) ) {
			ShutterTypeSupport ShutterTS = new ShutterTypeSupport();
			registerType(ShutterTS);
                        return SAL__OK;
		    }

                    if ( "camera_WAS".equals(topicName) ) {
			WASTypeSupport WASTS = new WASTypeSupport();
			registerType(WASTS);
                        return SAL__OK;
		    }

                    if ( "camera_WDS".equals(topicName) ) {
			WDSTypeSupport WDSTS = new WDSTypeSupport();
			registerType(WDSTS);
                        return SAL__OK;
		    }

                    if ( "camera_command_SetValue".equals(topicName) ) {
			command_SetValueTypeSupport command_SetValueTS = new command_SetValueTypeSupport();
			registerType(command_SetValueTS);
                        return SAL__OK;
		    }

                    if ( "camera_command_abort".equals(topicName) ) {
			command_abortTypeSupport command_abortTS = new command_abortTypeSupport();
			registerType(command_abortTS);
                        return SAL__OK;
		    }

                    if ( "camera_command_configure".equals(topicName) ) {
			command_configureTypeSupport command_configureTS = new command_configureTypeSupport();
			registerType(command_configureTS);
                        return SAL__OK;
		    }

                    if ( "camera_command_disable".equals(topicName) ) {
			command_disableTypeSupport command_disableTS = new command_disableTypeSupport();
			registerType(command_disableTS);
                        return SAL__OK;
		    }

                    if ( "camera_command_enable".equals(topicName) ) {
			command_enableTypeSupport command_enableTS = new command_enableTypeSupport();
			registerType(command_enableTS);
                        return SAL__OK;
		    }

                    if ( "camera_command_enterControl".equals(topicName) ) {
			command_enterControlTypeSupport command_enterControlTS = new command_enterControlTypeSupport();
			registerType(command_enterControlTS);
                        return SAL__OK;
		    }

                    if ( "camera_command_exitControl".equals(topicName) ) {
			command_exitControlTypeSupport command_exitControlTS = new command_exitControlTypeSupport();
			registerType(command_exitControlTS);
                        return SAL__OK;
		    }

                    if ( "camera_command_initGuiders".equals(topicName) ) {
			command_initGuidersTypeSupport command_initGuidersTS = new command_initGuidersTypeSupport();
			registerType(command_initGuidersTS);
                        return SAL__OK;
		    }

                    if ( "camera_command_initImage".equals(topicName) ) {
			command_initImageTypeSupport command_initImageTS = new command_initImageTypeSupport();
			registerType(command_initImageTS);
                        return SAL__OK;
		    }

                    if ( "camera_command_setFilter".equals(topicName) ) {
			command_setFilterTypeSupport command_setFilterTS = new command_setFilterTypeSupport();
			registerType(command_setFilterTS);
                        return SAL__OK;
		    }

                    if ( "camera_command_standby".equals(topicName) ) {
			command_standbyTypeSupport command_standbyTS = new command_standbyTypeSupport();
			registerType(command_standbyTS);
                        return SAL__OK;
		    }

                    if ( "camera_command_start".equals(topicName) ) {
			command_startTypeSupport command_startTS = new command_startTypeSupport();
			registerType(command_startTS);
                        return SAL__OK;
		    }

                    if ( "camera_command_stop".equals(topicName) ) {
			command_stopTypeSupport command_stopTS = new command_stopTypeSupport();
			registerType(command_stopTS);
                        return SAL__OK;
		    }

                    if ( "camera_command_takeImages".equals(topicName) ) {
			command_takeImagesTypeSupport command_takeImagesTS = new command_takeImagesTypeSupport();
			registerType(command_takeImagesTS);
                        return SAL__OK;
		    }

                    if ( "camera_logevent_AppliedSettingsMatchStart".equals(topicName) ) {
			logevent_AppliedSettingsMatchStartTypeSupport logevent_AppliedSettingsMatchStartTS = new logevent_AppliedSettingsMatchStartTypeSupport();
			registerType(logevent_AppliedSettingsMatchStartTS);
                        return SAL__OK;
		    }

                    if ( "camera_logevent_ErrorCode".equals(topicName) ) {
			logevent_ErrorCodeTypeSupport logevent_ErrorCodeTS = new logevent_ErrorCodeTypeSupport();
			registerType(logevent_ErrorCodeTS);
                        return SAL__OK;
		    }

                    if ( "camera_logevent_SettingVersions".equals(topicName) ) {
			logevent_SettingVersionsTypeSupport logevent_SettingVersionsTS = new logevent_SettingVersionsTypeSupport();
			registerType(logevent_SettingVersionsTS);
                        return SAL__OK;
		    }

                    if ( "camera_logevent_SummaryState".equals(topicName) ) {
			logevent_SummaryStateTypeSupport logevent_SummaryStateTS = new logevent_SummaryStateTypeSupport();
			registerType(logevent_SummaryStateTS);
                        return SAL__OK;
		    }

                    if ( "camera_logevent_ccsConfigured".equals(topicName) ) {
			logevent_ccsConfiguredTypeSupport logevent_ccsConfiguredTS = new logevent_ccsConfiguredTypeSupport();
			registerType(logevent_ccsConfiguredTS);
                        return SAL__OK;
		    }

                    if ( "camera_logevent_endInitializeGuider".equals(topicName) ) {
			logevent_endInitializeGuiderTypeSupport logevent_endInitializeGuiderTS = new logevent_endInitializeGuiderTypeSupport();
			registerType(logevent_endInitializeGuiderTS);
                        return SAL__OK;
		    }

                    if ( "camera_logevent_endInitializeImage".equals(topicName) ) {
			logevent_endInitializeImageTypeSupport logevent_endInitializeImageTS = new logevent_endInitializeImageTypeSupport();
			registerType(logevent_endInitializeImageTS);
                        return SAL__OK;
		    }

                    if ( "camera_logevent_endLoadFilter".equals(topicName) ) {
			logevent_endLoadFilterTypeSupport logevent_endLoadFilterTS = new logevent_endLoadFilterTypeSupport();
			registerType(logevent_endLoadFilterTS);
                        return SAL__OK;
		    }

                    if ( "camera_logevent_endReadout".equals(topicName) ) {
			logevent_endReadoutTypeSupport logevent_endReadoutTS = new logevent_endReadoutTypeSupport();
			registerType(logevent_endReadoutTS);
                        return SAL__OK;
		    }

                    if ( "camera_logevent_endRotateCarousel".equals(topicName) ) {
			logevent_endRotateCarouselTypeSupport logevent_endRotateCarouselTS = new logevent_endRotateCarouselTypeSupport();
			registerType(logevent_endRotateCarouselTS);
                        return SAL__OK;
		    }

                    if ( "camera_logevent_endSetFilter".equals(topicName) ) {
			logevent_endSetFilterTypeSupport logevent_endSetFilterTS = new logevent_endSetFilterTypeSupport();
			registerType(logevent_endSetFilterTS);
                        return SAL__OK;
		    }

                    if ( "camera_logevent_endShutterClose".equals(topicName) ) {
			logevent_endShutterCloseTypeSupport logevent_endShutterCloseTS = new logevent_endShutterCloseTypeSupport();
			registerType(logevent_endShutterCloseTS);
                        return SAL__OK;
		    }

                    if ( "camera_logevent_endShutterOpen".equals(topicName) ) {
			logevent_endShutterOpenTypeSupport logevent_endShutterOpenTS = new logevent_endShutterOpenTypeSupport();
			registerType(logevent_endShutterOpenTS);
                        return SAL__OK;
		    }

                    if ( "camera_logevent_endTakeImage".equals(topicName) ) {
			logevent_endTakeImageTypeSupport logevent_endTakeImageTS = new logevent_endTakeImageTypeSupport();
			registerType(logevent_endTakeImageTS);
                        return SAL__OK;
		    }

                    if ( "camera_logevent_endUnloadFilter".equals(topicName) ) {
			logevent_endUnloadFilterTypeSupport logevent_endUnloadFilterTS = new logevent_endUnloadFilterTypeSupport();
			registerType(logevent_endUnloadFilterTS);
                        return SAL__OK;
		    }

                    if ( "camera_logevent_notReadyToTakeImage".equals(topicName) ) {
			logevent_notReadyToTakeImageTypeSupport logevent_notReadyToTakeImageTS = new logevent_notReadyToTakeImageTypeSupport();
			registerType(logevent_notReadyToTakeImageTS);
                        return SAL__OK;
		    }

                    if ( "camera_logevent_prepareToTakeImage".equals(topicName) ) {
			logevent_prepareToTakeImageTypeSupport logevent_prepareToTakeImageTS = new logevent_prepareToTakeImageTypeSupport();
			registerType(logevent_prepareToTakeImageTS);
                        return SAL__OK;
		    }

                    if ( "camera_logevent_readyToTakeImage".equals(topicName) ) {
			logevent_readyToTakeImageTypeSupport logevent_readyToTakeImageTS = new logevent_readyToTakeImageTypeSupport();
			registerType(logevent_readyToTakeImageTS);
                        return SAL__OK;
		    }

                    if ( "camera_logevent_startIntegration".equals(topicName) ) {
			logevent_startIntegrationTypeSupport logevent_startIntegrationTS = new logevent_startIntegrationTypeSupport();
			registerType(logevent_startIntegrationTS);
                        return SAL__OK;
		    }

                    if ( "camera_logevent_startLoadFilter".equals(topicName) ) {
			logevent_startLoadFilterTypeSupport logevent_startLoadFilterTS = new logevent_startLoadFilterTypeSupport();
			registerType(logevent_startLoadFilterTS);
                        return SAL__OK;
		    }

                    if ( "camera_logevent_startReadout".equals(topicName) ) {
			logevent_startReadoutTypeSupport logevent_startReadoutTS = new logevent_startReadoutTypeSupport();
			registerType(logevent_startReadoutTS);
                        return SAL__OK;
		    }

                    if ( "camera_logevent_startRotateCarousel".equals(topicName) ) {
			logevent_startRotateCarouselTypeSupport logevent_startRotateCarouselTS = new logevent_startRotateCarouselTypeSupport();
			registerType(logevent_startRotateCarouselTS);
                        return SAL__OK;
		    }

                    if ( "camera_logevent_startSetFilter".equals(topicName) ) {
			logevent_startSetFilterTypeSupport logevent_startSetFilterTS = new logevent_startSetFilterTypeSupport();
			registerType(logevent_startSetFilterTS);
                        return SAL__OK;
		    }

                    if ( "camera_logevent_startShutterClose".equals(topicName) ) {
			logevent_startShutterCloseTypeSupport logevent_startShutterCloseTS = new logevent_startShutterCloseTypeSupport();
			registerType(logevent_startShutterCloseTS);
                        return SAL__OK;
		    }

                    if ( "camera_logevent_startShutterOpen".equals(topicName) ) {
			logevent_startShutterOpenTypeSupport logevent_startShutterOpenTS = new logevent_startShutterOpenTypeSupport();
			registerType(logevent_startShutterOpenTS);
                        return SAL__OK;
		    }

                    if ( "camera_logevent_startUnloadFilter".equals(topicName) ) {
			logevent_startUnloadFilterTypeSupport logevent_startUnloadFilterTS = new logevent_startUnloadFilterTypeSupport();
			registerType(logevent_startUnloadFilterTS);
                        return SAL__OK;
		    }

                    if ( "camera_command".equals(topicName) ) {
			commandTypeSupport commandTS = new commandTypeSupport();
			registerType(commandTS);
                        return SAL__OK;
		    }

                    if ( "camera_ackcmd".equals(topicName) ) {
			ackcmdTypeSupport ackcmdTS = new ackcmdTypeSupport();
			registerType(ackcmdTS);
                        return SAL__OK;
		    }

                    if ( "camera_logevent".equals(topicName) ) {
			logeventTypeSupport logeventTS = new logeventTypeSupport();
			registerType(logeventTS);
                        return SAL__OK;
		    }
	 }

  return SAL__ERR;
}
        public int salTypeSupport(int actorIdx) {

                    if ( actorIdx == SAL__camera_CCS_ACTOR ) {
			CCSTypeSupport CCSTS = new CCSTypeSupport();
			registerType(actorIdx,CCSTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_Cluster_Encoder_ACTOR ) {
			Cluster_EncoderTypeSupport Cluster_EncoderTS = new Cluster_EncoderTypeSupport();
			registerType(actorIdx,Cluster_EncoderTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_Cold_ACTOR ) {
			ColdTypeSupport ColdTS = new ColdTypeSupport();
			registerType(actorIdx,ColdTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_Cryo_ACTOR ) {
			CryoTypeSupport CryoTS = new CryoTypeSupport();
			registerType(actorIdx,CryoTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_Filter_ACTOR ) {
			FilterTypeSupport FilterTS = new FilterTypeSupport();
			registerType(actorIdx,FilterTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_GAS_ACTOR ) {
			GASTypeSupport GASTS = new GASTypeSupport();
			registerType(actorIdx,GASTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_GDS_ACTOR ) {
			GDSTypeSupport GDSTS = new GDSTypeSupport();
			registerType(actorIdx,GDSTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_PCMS_ACTOR ) {
			PCMSTypeSupport PCMSTS = new PCMSTypeSupport();
			registerType(actorIdx,PCMSTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_Prot_ACTOR ) {
			ProtTypeSupport ProtTS = new ProtTypeSupport();
			registerType(actorIdx,ProtTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_Purge_ACTOR ) {
			PurgeTypeSupport PurgeTS = new PurgeTypeSupport();
			registerType(actorIdx,PurgeTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_SAS_ACTOR ) {
			SASTypeSupport SASTS = new SASTypeSupport();
			registerType(actorIdx,SASTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_SDS_ACTOR ) {
			SDSTypeSupport SDSTS = new SDSTypeSupport();
			registerType(actorIdx,SDSTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_Shutter_ACTOR ) {
			ShutterTypeSupport ShutterTS = new ShutterTypeSupport();
			registerType(actorIdx,ShutterTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_WAS_ACTOR ) {
			WASTypeSupport WASTS = new WASTypeSupport();
			registerType(actorIdx,WASTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_WDS_ACTOR ) {
			WDSTypeSupport WDSTS = new WDSTypeSupport();
			registerType(actorIdx,WDSTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_command_SetValue_ACTOR ) {
			command_SetValueTypeSupport command_SetValueTS = new command_SetValueTypeSupport();
			registerType(actorIdx,command_SetValueTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_command_abort_ACTOR ) {
			command_abortTypeSupport command_abortTS = new command_abortTypeSupport();
			registerType(actorIdx,command_abortTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_command_configure_ACTOR ) {
			command_configureTypeSupport command_configureTS = new command_configureTypeSupport();
			registerType(actorIdx,command_configureTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_command_disable_ACTOR ) {
			command_disableTypeSupport command_disableTS = new command_disableTypeSupport();
			registerType(actorIdx,command_disableTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_command_enable_ACTOR ) {
			command_enableTypeSupport command_enableTS = new command_enableTypeSupport();
			registerType(actorIdx,command_enableTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_command_enterControl_ACTOR ) {
			command_enterControlTypeSupport command_enterControlTS = new command_enterControlTypeSupport();
			registerType(actorIdx,command_enterControlTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_command_exitControl_ACTOR ) {
			command_exitControlTypeSupport command_exitControlTS = new command_exitControlTypeSupport();
			registerType(actorIdx,command_exitControlTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_command_initGuiders_ACTOR ) {
			command_initGuidersTypeSupport command_initGuidersTS = new command_initGuidersTypeSupport();
			registerType(actorIdx,command_initGuidersTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_command_initImage_ACTOR ) {
			command_initImageTypeSupport command_initImageTS = new command_initImageTypeSupport();
			registerType(actorIdx,command_initImageTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_command_setFilter_ACTOR ) {
			command_setFilterTypeSupport command_setFilterTS = new command_setFilterTypeSupport();
			registerType(actorIdx,command_setFilterTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_command_standby_ACTOR ) {
			command_standbyTypeSupport command_standbyTS = new command_standbyTypeSupport();
			registerType(actorIdx,command_standbyTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_command_start_ACTOR ) {
			command_startTypeSupport command_startTS = new command_startTypeSupport();
			registerType(actorIdx,command_startTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_command_stop_ACTOR ) {
			command_stopTypeSupport command_stopTS = new command_stopTypeSupport();
			registerType(actorIdx,command_stopTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_command_takeImages_ACTOR ) {
			command_takeImagesTypeSupport command_takeImagesTS = new command_takeImagesTypeSupport();
			registerType(actorIdx,command_takeImagesTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_logevent_AppliedSettingsMatchStart_ACTOR ) {
			logevent_AppliedSettingsMatchStartTypeSupport logevent_AppliedSettingsMatchStartTS = new logevent_AppliedSettingsMatchStartTypeSupport();
			registerType(actorIdx,logevent_AppliedSettingsMatchStartTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_logevent_ErrorCode_ACTOR ) {
			logevent_ErrorCodeTypeSupport logevent_ErrorCodeTS = new logevent_ErrorCodeTypeSupport();
			registerType(actorIdx,logevent_ErrorCodeTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_logevent_SettingVersions_ACTOR ) {
			logevent_SettingVersionsTypeSupport logevent_SettingVersionsTS = new logevent_SettingVersionsTypeSupport();
			registerType(actorIdx,logevent_SettingVersionsTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_logevent_SummaryState_ACTOR ) {
			logevent_SummaryStateTypeSupport logevent_SummaryStateTS = new logevent_SummaryStateTypeSupport();
			registerType(actorIdx,logevent_SummaryStateTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_logevent_ccsConfigured_ACTOR ) {
			logevent_ccsConfiguredTypeSupport logevent_ccsConfiguredTS = new logevent_ccsConfiguredTypeSupport();
			registerType(actorIdx,logevent_ccsConfiguredTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_logevent_endInitializeGuider_ACTOR ) {
			logevent_endInitializeGuiderTypeSupport logevent_endInitializeGuiderTS = new logevent_endInitializeGuiderTypeSupport();
			registerType(actorIdx,logevent_endInitializeGuiderTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_logevent_endInitializeImage_ACTOR ) {
			logevent_endInitializeImageTypeSupport logevent_endInitializeImageTS = new logevent_endInitializeImageTypeSupport();
			registerType(actorIdx,logevent_endInitializeImageTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_logevent_endLoadFilter_ACTOR ) {
			logevent_endLoadFilterTypeSupport logevent_endLoadFilterTS = new logevent_endLoadFilterTypeSupport();
			registerType(actorIdx,logevent_endLoadFilterTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_logevent_endReadout_ACTOR ) {
			logevent_endReadoutTypeSupport logevent_endReadoutTS = new logevent_endReadoutTypeSupport();
			registerType(actorIdx,logevent_endReadoutTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_logevent_endRotateCarousel_ACTOR ) {
			logevent_endRotateCarouselTypeSupport logevent_endRotateCarouselTS = new logevent_endRotateCarouselTypeSupport();
			registerType(actorIdx,logevent_endRotateCarouselTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_logevent_endSetFilter_ACTOR ) {
			logevent_endSetFilterTypeSupport logevent_endSetFilterTS = new logevent_endSetFilterTypeSupport();
			registerType(actorIdx,logevent_endSetFilterTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_logevent_endShutterClose_ACTOR ) {
			logevent_endShutterCloseTypeSupport logevent_endShutterCloseTS = new logevent_endShutterCloseTypeSupport();
			registerType(actorIdx,logevent_endShutterCloseTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_logevent_endShutterOpen_ACTOR ) {
			logevent_endShutterOpenTypeSupport logevent_endShutterOpenTS = new logevent_endShutterOpenTypeSupport();
			registerType(actorIdx,logevent_endShutterOpenTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_logevent_endTakeImage_ACTOR ) {
			logevent_endTakeImageTypeSupport logevent_endTakeImageTS = new logevent_endTakeImageTypeSupport();
			registerType(actorIdx,logevent_endTakeImageTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_logevent_endUnloadFilter_ACTOR ) {
			logevent_endUnloadFilterTypeSupport logevent_endUnloadFilterTS = new logevent_endUnloadFilterTypeSupport();
			registerType(actorIdx,logevent_endUnloadFilterTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_logevent_notReadyToTakeImage_ACTOR ) {
			logevent_notReadyToTakeImageTypeSupport logevent_notReadyToTakeImageTS = new logevent_notReadyToTakeImageTypeSupport();
			registerType(actorIdx,logevent_notReadyToTakeImageTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_logevent_prepareToTakeImage_ACTOR ) {
			logevent_prepareToTakeImageTypeSupport logevent_prepareToTakeImageTS = new logevent_prepareToTakeImageTypeSupport();
			registerType(actorIdx,logevent_prepareToTakeImageTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_logevent_readyToTakeImage_ACTOR ) {
			logevent_readyToTakeImageTypeSupport logevent_readyToTakeImageTS = new logevent_readyToTakeImageTypeSupport();
			registerType(actorIdx,logevent_readyToTakeImageTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_logevent_startIntegration_ACTOR ) {
			logevent_startIntegrationTypeSupport logevent_startIntegrationTS = new logevent_startIntegrationTypeSupport();
			registerType(actorIdx,logevent_startIntegrationTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_logevent_startLoadFilter_ACTOR ) {
			logevent_startLoadFilterTypeSupport logevent_startLoadFilterTS = new logevent_startLoadFilterTypeSupport();
			registerType(actorIdx,logevent_startLoadFilterTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_logevent_startReadout_ACTOR ) {
			logevent_startReadoutTypeSupport logevent_startReadoutTS = new logevent_startReadoutTypeSupport();
			registerType(actorIdx,logevent_startReadoutTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_logevent_startRotateCarousel_ACTOR ) {
			logevent_startRotateCarouselTypeSupport logevent_startRotateCarouselTS = new logevent_startRotateCarouselTypeSupport();
			registerType(actorIdx,logevent_startRotateCarouselTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_logevent_startSetFilter_ACTOR ) {
			logevent_startSetFilterTypeSupport logevent_startSetFilterTS = new logevent_startSetFilterTypeSupport();
			registerType(actorIdx,logevent_startSetFilterTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_logevent_startShutterClose_ACTOR ) {
			logevent_startShutterCloseTypeSupport logevent_startShutterCloseTS = new logevent_startShutterCloseTypeSupport();
			registerType(actorIdx,logevent_startShutterCloseTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_logevent_startShutterOpen_ACTOR ) {
			logevent_startShutterOpenTypeSupport logevent_startShutterOpenTS = new logevent_startShutterOpenTypeSupport();
			registerType(actorIdx,logevent_startShutterOpenTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_logevent_startUnloadFilter_ACTOR ) {
			logevent_startUnloadFilterTypeSupport logevent_startUnloadFilterTS = new logevent_startUnloadFilterTypeSupport();
			registerType(actorIdx,logevent_startUnloadFilterTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_command_ACTOR ) {
			commandTypeSupport commandTS = new commandTypeSupport();
			registerType(actorIdx,commandTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_ackcmd_ACTOR ) {
			ackcmdTypeSupport ackcmdTS = new ackcmdTypeSupport();
			registerType(actorIdx,ackcmdTS);
                        return SAL__OK;
		    }

                    if ( actorIdx == SAL__camera_logevent_ACTOR ) {
			logeventTypeSupport logeventTS = new logeventTypeSupport();
			registerType(actorIdx,logeventTS);
                        return SAL__OK;
		    }

  return SAL__ERR;
}

	public int putSample(camera.CCS data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_CCS_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  CCSDataWriter SALWriter = CCSDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample CCS] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "CCSDataWriter.write");

	  return status;
	}


	public int getSample(camera.CCS data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          CCSSeqHolder SALInstance = new CCSSeqHolder();
	  int actorIdx = SAL__camera_CCS_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  CCSDataReader SALReader = CCSDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample CCS ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.CCS data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_CCS_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.CCS data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_CCS_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.Cluster_Encoder data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_Cluster_Encoder_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  Cluster_EncoderDataWriter SALWriter = Cluster_EncoderDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample Cluster_Encoder] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "Cluster_EncoderDataWriter.write");

	  return status;
	}


	public int getSample(camera.Cluster_Encoder data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          Cluster_EncoderSeqHolder SALInstance = new Cluster_EncoderSeqHolder();
	  int actorIdx = SAL__camera_Cluster_Encoder_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  Cluster_EncoderDataReader SALReader = Cluster_EncoderDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample Cluster_Encoder ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.Cluster_Encoder data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_Cluster_Encoder_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.Cluster_Encoder data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_Cluster_Encoder_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.Cold data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_Cold_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  ColdDataWriter SALWriter = ColdDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample Cold] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "ColdDataWriter.write");

	  return status;
	}


	public int getSample(camera.Cold data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          ColdSeqHolder SALInstance = new ColdSeqHolder();
	  int actorIdx = SAL__camera_Cold_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  ColdDataReader SALReader = ColdDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample Cold ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.Cold data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_Cold_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.Cold data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_Cold_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.Cryo data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_Cryo_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  CryoDataWriter SALWriter = CryoDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample Cryo] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "CryoDataWriter.write");

	  return status;
	}


	public int getSample(camera.Cryo data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          CryoSeqHolder SALInstance = new CryoSeqHolder();
	  int actorIdx = SAL__camera_Cryo_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  CryoDataReader SALReader = CryoDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample Cryo ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.Cryo data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_Cryo_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.Cryo data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_Cryo_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.Filter data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_Filter_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  FilterDataWriter SALWriter = FilterDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample Filter] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "FilterDataWriter.write");

	  return status;
	}


	public int getSample(camera.Filter data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          FilterSeqHolder SALInstance = new FilterSeqHolder();
	  int actorIdx = SAL__camera_Filter_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  FilterDataReader SALReader = FilterDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample Filter ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.Filter data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_Filter_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.Filter data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_Filter_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.GAS data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_GAS_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  GASDataWriter SALWriter = GASDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample GAS] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "GASDataWriter.write");

	  return status;
	}


	public int getSample(camera.GAS data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          GASSeqHolder SALInstance = new GASSeqHolder();
	  int actorIdx = SAL__camera_GAS_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  GASDataReader SALReader = GASDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample GAS ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.GAS data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_GAS_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.GAS data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_GAS_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.GDS data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_GDS_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  GDSDataWriter SALWriter = GDSDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample GDS] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "GDSDataWriter.write");

	  return status;
	}


	public int getSample(camera.GDS data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          GDSSeqHolder SALInstance = new GDSSeqHolder();
	  int actorIdx = SAL__camera_GDS_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  GDSDataReader SALReader = GDSDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample GDS ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.GDS data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_GDS_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.GDS data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_GDS_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.PCMS data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_PCMS_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  PCMSDataWriter SALWriter = PCMSDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample PCMS] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "PCMSDataWriter.write");

	  return status;
	}


	public int getSample(camera.PCMS data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          PCMSSeqHolder SALInstance = new PCMSSeqHolder();
	  int actorIdx = SAL__camera_PCMS_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  PCMSDataReader SALReader = PCMSDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample PCMS ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.PCMS data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_PCMS_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.PCMS data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_PCMS_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.Prot data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_Prot_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  ProtDataWriter SALWriter = ProtDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample Prot] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "ProtDataWriter.write");

	  return status;
	}


	public int getSample(camera.Prot data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          ProtSeqHolder SALInstance = new ProtSeqHolder();
	  int actorIdx = SAL__camera_Prot_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  ProtDataReader SALReader = ProtDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample Prot ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.Prot data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_Prot_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.Prot data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_Prot_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.Purge data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_Purge_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  PurgeDataWriter SALWriter = PurgeDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample Purge] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "PurgeDataWriter.write");

	  return status;
	}


	public int getSample(camera.Purge data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          PurgeSeqHolder SALInstance = new PurgeSeqHolder();
	  int actorIdx = SAL__camera_Purge_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  PurgeDataReader SALReader = PurgeDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample Purge ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.Purge data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_Purge_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.Purge data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_Purge_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.SAS data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_SAS_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  SASDataWriter SALWriter = SASDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample SAS] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "SASDataWriter.write");

	  return status;
	}


	public int getSample(camera.SAS data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          SASSeqHolder SALInstance = new SASSeqHolder();
	  int actorIdx = SAL__camera_SAS_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  SASDataReader SALReader = SASDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample SAS ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.SAS data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_SAS_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.SAS data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_SAS_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.SDS data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_SDS_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  SDSDataWriter SALWriter = SDSDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample SDS] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "SDSDataWriter.write");

	  return status;
	}


	public int getSample(camera.SDS data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          SDSSeqHolder SALInstance = new SDSSeqHolder();
	  int actorIdx = SAL__camera_SDS_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  SDSDataReader SALReader = SDSDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample SDS ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.SDS data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_SDS_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.SDS data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_SDS_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.Shutter data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_Shutter_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  ShutterDataWriter SALWriter = ShutterDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample Shutter] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "ShutterDataWriter.write");

	  return status;
	}


	public int getSample(camera.Shutter data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          ShutterSeqHolder SALInstance = new ShutterSeqHolder();
	  int actorIdx = SAL__camera_Shutter_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  ShutterDataReader SALReader = ShutterDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample Shutter ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.Shutter data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_Shutter_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.Shutter data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_Shutter_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.WAS data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_WAS_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  WASDataWriter SALWriter = WASDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample WAS] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "WASDataWriter.write");

	  return status;
	}


	public int getSample(camera.WAS data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          WASSeqHolder SALInstance = new WASSeqHolder();
	  int actorIdx = SAL__camera_WAS_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  WASDataReader SALReader = WASDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample WAS ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.WAS data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_WAS_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.WAS data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_WAS_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.WDS data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_WDS_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  WDSDataWriter SALWriter = WDSDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample WDS] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "WDSDataWriter.write");

	  return status;
	}


	public int getSample(camera.WDS data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          WDSSeqHolder SALInstance = new WDSSeqHolder();
	  int actorIdx = SAL__camera_WDS_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  WDSDataReader SALReader = WDSDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample WDS ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.WDS data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_WDS_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.WDS data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_WDS_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.command_SetValue data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_command_SetValue_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  command_SetValueDataWriter SALWriter = command_SetValueDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample command_SetValue] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "command_SetValueDataWriter.write");

	  return status;
	}


	public int getSample(camera.command_SetValue data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          command_SetValueSeqHolder SALInstance = new command_SetValueSeqHolder();
	  int actorIdx = SAL__camera_command_SetValue_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  command_SetValueDataReader SALReader = command_SetValueDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample command_SetValue ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.command_SetValue data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_command_SetValue_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.command_SetValue data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_command_SetValue_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.command_abort data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_command_abort_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  command_abortDataWriter SALWriter = command_abortDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample command_abort] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "command_abortDataWriter.write");

	  return status;
	}


	public int getSample(camera.command_abort data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          command_abortSeqHolder SALInstance = new command_abortSeqHolder();
	  int actorIdx = SAL__camera_command_abort_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  command_abortDataReader SALReader = command_abortDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample command_abort ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.command_abort data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_command_abort_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.command_abort data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_command_abort_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.command_configure data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_command_configure_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  command_configureDataWriter SALWriter = command_configureDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample command_configure] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "command_configureDataWriter.write");

	  return status;
	}


	public int getSample(camera.command_configure data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          command_configureSeqHolder SALInstance = new command_configureSeqHolder();
	  int actorIdx = SAL__camera_command_configure_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  command_configureDataReader SALReader = command_configureDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample command_configure ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.command_configure data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_command_configure_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.command_configure data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_command_configure_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.command_disable data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_command_disable_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  command_disableDataWriter SALWriter = command_disableDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample command_disable] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "command_disableDataWriter.write");

	  return status;
	}


	public int getSample(camera.command_disable data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          command_disableSeqHolder SALInstance = new command_disableSeqHolder();
	  int actorIdx = SAL__camera_command_disable_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  command_disableDataReader SALReader = command_disableDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample command_disable ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.command_disable data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_command_disable_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.command_disable data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_command_disable_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.command_enable data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_command_enable_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  command_enableDataWriter SALWriter = command_enableDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample command_enable] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "command_enableDataWriter.write");

	  return status;
	}


	public int getSample(camera.command_enable data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          command_enableSeqHolder SALInstance = new command_enableSeqHolder();
	  int actorIdx = SAL__camera_command_enable_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  command_enableDataReader SALReader = command_enableDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample command_enable ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.command_enable data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_command_enable_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.command_enable data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_command_enable_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.command_enterControl data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_command_enterControl_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  command_enterControlDataWriter SALWriter = command_enterControlDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample command_enterControl] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "command_enterControlDataWriter.write");

	  return status;
	}


	public int getSample(camera.command_enterControl data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          command_enterControlSeqHolder SALInstance = new command_enterControlSeqHolder();
	  int actorIdx = SAL__camera_command_enterControl_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  command_enterControlDataReader SALReader = command_enterControlDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample command_enterControl ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.command_enterControl data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_command_enterControl_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.command_enterControl data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_command_enterControl_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.command_exitControl data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_command_exitControl_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  command_exitControlDataWriter SALWriter = command_exitControlDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample command_exitControl] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "command_exitControlDataWriter.write");

	  return status;
	}


	public int getSample(camera.command_exitControl data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          command_exitControlSeqHolder SALInstance = new command_exitControlSeqHolder();
	  int actorIdx = SAL__camera_command_exitControl_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  command_exitControlDataReader SALReader = command_exitControlDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample command_exitControl ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.command_exitControl data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_command_exitControl_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.command_exitControl data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_command_exitControl_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.command_initGuiders data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_command_initGuiders_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  command_initGuidersDataWriter SALWriter = command_initGuidersDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample command_initGuiders] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "command_initGuidersDataWriter.write");

	  return status;
	}


	public int getSample(camera.command_initGuiders data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          command_initGuidersSeqHolder SALInstance = new command_initGuidersSeqHolder();
	  int actorIdx = SAL__camera_command_initGuiders_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  command_initGuidersDataReader SALReader = command_initGuidersDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample command_initGuiders ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.command_initGuiders data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_command_initGuiders_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.command_initGuiders data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_command_initGuiders_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.command_initImage data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_command_initImage_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  command_initImageDataWriter SALWriter = command_initImageDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample command_initImage] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "command_initImageDataWriter.write");

	  return status;
	}


	public int getSample(camera.command_initImage data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          command_initImageSeqHolder SALInstance = new command_initImageSeqHolder();
	  int actorIdx = SAL__camera_command_initImage_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  command_initImageDataReader SALReader = command_initImageDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample command_initImage ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.command_initImage data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_command_initImage_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.command_initImage data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_command_initImage_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.command_setFilter data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_command_setFilter_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  command_setFilterDataWriter SALWriter = command_setFilterDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample command_setFilter] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "command_setFilterDataWriter.write");

	  return status;
	}


	public int getSample(camera.command_setFilter data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          command_setFilterSeqHolder SALInstance = new command_setFilterSeqHolder();
	  int actorIdx = SAL__camera_command_setFilter_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  command_setFilterDataReader SALReader = command_setFilterDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample command_setFilter ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.command_setFilter data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_command_setFilter_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.command_setFilter data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_command_setFilter_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.command_standby data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_command_standby_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  command_standbyDataWriter SALWriter = command_standbyDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample command_standby] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "command_standbyDataWriter.write");

	  return status;
	}


	public int getSample(camera.command_standby data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          command_standbySeqHolder SALInstance = new command_standbySeqHolder();
	  int actorIdx = SAL__camera_command_standby_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  command_standbyDataReader SALReader = command_standbyDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample command_standby ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.command_standby data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_command_standby_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.command_standby data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_command_standby_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.command_start data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_command_start_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  command_startDataWriter SALWriter = command_startDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample command_start] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "command_startDataWriter.write");

	  return status;
	}


	public int getSample(camera.command_start data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          command_startSeqHolder SALInstance = new command_startSeqHolder();
	  int actorIdx = SAL__camera_command_start_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  command_startDataReader SALReader = command_startDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample command_start ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.command_start data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_command_start_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.command_start data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_command_start_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.command_stop data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_command_stop_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  command_stopDataWriter SALWriter = command_stopDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample command_stop] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "command_stopDataWriter.write");

	  return status;
	}


	public int getSample(camera.command_stop data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          command_stopSeqHolder SALInstance = new command_stopSeqHolder();
	  int actorIdx = SAL__camera_command_stop_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  command_stopDataReader SALReader = command_stopDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample command_stop ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.command_stop data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_command_stop_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.command_stop data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_command_stop_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.command_takeImages data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_command_takeImages_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  command_takeImagesDataWriter SALWriter = command_takeImagesDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample command_takeImages] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "command_takeImagesDataWriter.write");

	  return status;
	}


	public int getSample(camera.command_takeImages data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          command_takeImagesSeqHolder SALInstance = new command_takeImagesSeqHolder();
	  int actorIdx = SAL__camera_command_takeImages_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  command_takeImagesDataReader SALReader = command_takeImagesDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample command_takeImages ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.command_takeImages data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_command_takeImages_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.command_takeImages data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_command_takeImages_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.logevent_AppliedSettingsMatchStart data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_logevent_AppliedSettingsMatchStart_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  logevent_AppliedSettingsMatchStartDataWriter SALWriter = logevent_AppliedSettingsMatchStartDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample logevent_AppliedSettingsMatchStart] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "logevent_AppliedSettingsMatchStartDataWriter.write");

	  return status;
	}


	public int getSample(camera.logevent_AppliedSettingsMatchStart data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          logevent_AppliedSettingsMatchStartSeqHolder SALInstance = new logevent_AppliedSettingsMatchStartSeqHolder();
	  int actorIdx = SAL__camera_logevent_AppliedSettingsMatchStart_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  logevent_AppliedSettingsMatchStartDataReader SALReader = logevent_AppliedSettingsMatchStartDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample logevent_AppliedSettingsMatchStart ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.logevent_AppliedSettingsMatchStart data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_logevent_AppliedSettingsMatchStart_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.logevent_AppliedSettingsMatchStart data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_logevent_AppliedSettingsMatchStart_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.logevent_ErrorCode data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_logevent_ErrorCode_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  logevent_ErrorCodeDataWriter SALWriter = logevent_ErrorCodeDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample logevent_ErrorCode] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "logevent_ErrorCodeDataWriter.write");

	  return status;
	}


	public int getSample(camera.logevent_ErrorCode data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          logevent_ErrorCodeSeqHolder SALInstance = new logevent_ErrorCodeSeqHolder();
	  int actorIdx = SAL__camera_logevent_ErrorCode_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  logevent_ErrorCodeDataReader SALReader = logevent_ErrorCodeDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample logevent_ErrorCode ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.logevent_ErrorCode data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_logevent_ErrorCode_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.logevent_ErrorCode data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_logevent_ErrorCode_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.logevent_SettingVersions data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_logevent_SettingVersions_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  logevent_SettingVersionsDataWriter SALWriter = logevent_SettingVersionsDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample logevent_SettingVersions] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "logevent_SettingVersionsDataWriter.write");

	  return status;
	}


	public int getSample(camera.logevent_SettingVersions data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          logevent_SettingVersionsSeqHolder SALInstance = new logevent_SettingVersionsSeqHolder();
	  int actorIdx = SAL__camera_logevent_SettingVersions_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  logevent_SettingVersionsDataReader SALReader = logevent_SettingVersionsDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample logevent_SettingVersions ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.logevent_SettingVersions data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_logevent_SettingVersions_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.logevent_SettingVersions data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_logevent_SettingVersions_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.logevent_SummaryState data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_logevent_SummaryState_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  logevent_SummaryStateDataWriter SALWriter = logevent_SummaryStateDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample logevent_SummaryState] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "logevent_SummaryStateDataWriter.write");

	  return status;
	}


	public int getSample(camera.logevent_SummaryState data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          logevent_SummaryStateSeqHolder SALInstance = new logevent_SummaryStateSeqHolder();
	  int actorIdx = SAL__camera_logevent_SummaryState_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  logevent_SummaryStateDataReader SALReader = logevent_SummaryStateDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample logevent_SummaryState ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.logevent_SummaryState data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_logevent_SummaryState_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.logevent_SummaryState data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_logevent_SummaryState_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.logevent_ccsConfigured data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_logevent_ccsConfigured_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  logevent_ccsConfiguredDataWriter SALWriter = logevent_ccsConfiguredDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample logevent_ccsConfigured] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "logevent_ccsConfiguredDataWriter.write");

	  return status;
	}


	public int getSample(camera.logevent_ccsConfigured data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          logevent_ccsConfiguredSeqHolder SALInstance = new logevent_ccsConfiguredSeqHolder();
	  int actorIdx = SAL__camera_logevent_ccsConfigured_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  logevent_ccsConfiguredDataReader SALReader = logevent_ccsConfiguredDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample logevent_ccsConfigured ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.logevent_ccsConfigured data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_logevent_ccsConfigured_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.logevent_ccsConfigured data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_logevent_ccsConfigured_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.logevent_endInitializeGuider data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_logevent_endInitializeGuider_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  logevent_endInitializeGuiderDataWriter SALWriter = logevent_endInitializeGuiderDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample logevent_endInitializeGuider] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "logevent_endInitializeGuiderDataWriter.write");

	  return status;
	}


	public int getSample(camera.logevent_endInitializeGuider data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          logevent_endInitializeGuiderSeqHolder SALInstance = new logevent_endInitializeGuiderSeqHolder();
	  int actorIdx = SAL__camera_logevent_endInitializeGuider_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  logevent_endInitializeGuiderDataReader SALReader = logevent_endInitializeGuiderDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample logevent_endInitializeGuider ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.logevent_endInitializeGuider data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_logevent_endInitializeGuider_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.logevent_endInitializeGuider data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_logevent_endInitializeGuider_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.logevent_endInitializeImage data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_logevent_endInitializeImage_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  logevent_endInitializeImageDataWriter SALWriter = logevent_endInitializeImageDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample logevent_endInitializeImage] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "logevent_endInitializeImageDataWriter.write");

	  return status;
	}


	public int getSample(camera.logevent_endInitializeImage data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          logevent_endInitializeImageSeqHolder SALInstance = new logevent_endInitializeImageSeqHolder();
	  int actorIdx = SAL__camera_logevent_endInitializeImage_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  logevent_endInitializeImageDataReader SALReader = logevent_endInitializeImageDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample logevent_endInitializeImage ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.logevent_endInitializeImage data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_logevent_endInitializeImage_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.logevent_endInitializeImage data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_logevent_endInitializeImage_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.logevent_endLoadFilter data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_logevent_endLoadFilter_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  logevent_endLoadFilterDataWriter SALWriter = logevent_endLoadFilterDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample logevent_endLoadFilter] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "logevent_endLoadFilterDataWriter.write");

	  return status;
	}


	public int getSample(camera.logevent_endLoadFilter data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          logevent_endLoadFilterSeqHolder SALInstance = new logevent_endLoadFilterSeqHolder();
	  int actorIdx = SAL__camera_logevent_endLoadFilter_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  logevent_endLoadFilterDataReader SALReader = logevent_endLoadFilterDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample logevent_endLoadFilter ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.logevent_endLoadFilter data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_logevent_endLoadFilter_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.logevent_endLoadFilter data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_logevent_endLoadFilter_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.logevent_endReadout data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_logevent_endReadout_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  logevent_endReadoutDataWriter SALWriter = logevent_endReadoutDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample logevent_endReadout] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "logevent_endReadoutDataWriter.write");

	  return status;
	}


	public int getSample(camera.logevent_endReadout data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          logevent_endReadoutSeqHolder SALInstance = new logevent_endReadoutSeqHolder();
	  int actorIdx = SAL__camera_logevent_endReadout_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  logevent_endReadoutDataReader SALReader = logevent_endReadoutDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample logevent_endReadout ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.logevent_endReadout data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_logevent_endReadout_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.logevent_endReadout data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_logevent_endReadout_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.logevent_endRotateCarousel data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_logevent_endRotateCarousel_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  logevent_endRotateCarouselDataWriter SALWriter = logevent_endRotateCarouselDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample logevent_endRotateCarousel] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "logevent_endRotateCarouselDataWriter.write");

	  return status;
	}


	public int getSample(camera.logevent_endRotateCarousel data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          logevent_endRotateCarouselSeqHolder SALInstance = new logevent_endRotateCarouselSeqHolder();
	  int actorIdx = SAL__camera_logevent_endRotateCarousel_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  logevent_endRotateCarouselDataReader SALReader = logevent_endRotateCarouselDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample logevent_endRotateCarousel ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.logevent_endRotateCarousel data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_logevent_endRotateCarousel_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.logevent_endRotateCarousel data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_logevent_endRotateCarousel_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.logevent_endSetFilter data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_logevent_endSetFilter_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  logevent_endSetFilterDataWriter SALWriter = logevent_endSetFilterDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample logevent_endSetFilter] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "logevent_endSetFilterDataWriter.write");

	  return status;
	}


	public int getSample(camera.logevent_endSetFilter data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          logevent_endSetFilterSeqHolder SALInstance = new logevent_endSetFilterSeqHolder();
	  int actorIdx = SAL__camera_logevent_endSetFilter_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  logevent_endSetFilterDataReader SALReader = logevent_endSetFilterDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample logevent_endSetFilter ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.logevent_endSetFilter data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_logevent_endSetFilter_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.logevent_endSetFilter data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_logevent_endSetFilter_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.logevent_endShutterClose data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_logevent_endShutterClose_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  logevent_endShutterCloseDataWriter SALWriter = logevent_endShutterCloseDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample logevent_endShutterClose] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "logevent_endShutterCloseDataWriter.write");

	  return status;
	}


	public int getSample(camera.logevent_endShutterClose data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          logevent_endShutterCloseSeqHolder SALInstance = new logevent_endShutterCloseSeqHolder();
	  int actorIdx = SAL__camera_logevent_endShutterClose_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  logevent_endShutterCloseDataReader SALReader = logevent_endShutterCloseDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample logevent_endShutterClose ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.logevent_endShutterClose data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_logevent_endShutterClose_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.logevent_endShutterClose data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_logevent_endShutterClose_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.logevent_endShutterOpen data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_logevent_endShutterOpen_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  logevent_endShutterOpenDataWriter SALWriter = logevent_endShutterOpenDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample logevent_endShutterOpen] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "logevent_endShutterOpenDataWriter.write");

	  return status;
	}


	public int getSample(camera.logevent_endShutterOpen data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          logevent_endShutterOpenSeqHolder SALInstance = new logevent_endShutterOpenSeqHolder();
	  int actorIdx = SAL__camera_logevent_endShutterOpen_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  logevent_endShutterOpenDataReader SALReader = logevent_endShutterOpenDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample logevent_endShutterOpen ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.logevent_endShutterOpen data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_logevent_endShutterOpen_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.logevent_endShutterOpen data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_logevent_endShutterOpen_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.logevent_endTakeImage data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_logevent_endTakeImage_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  logevent_endTakeImageDataWriter SALWriter = logevent_endTakeImageDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample logevent_endTakeImage] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "logevent_endTakeImageDataWriter.write");

	  return status;
	}


	public int getSample(camera.logevent_endTakeImage data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          logevent_endTakeImageSeqHolder SALInstance = new logevent_endTakeImageSeqHolder();
	  int actorIdx = SAL__camera_logevent_endTakeImage_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  logevent_endTakeImageDataReader SALReader = logevent_endTakeImageDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample logevent_endTakeImage ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.logevent_endTakeImage data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_logevent_endTakeImage_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.logevent_endTakeImage data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_logevent_endTakeImage_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.logevent_endUnloadFilter data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_logevent_endUnloadFilter_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  logevent_endUnloadFilterDataWriter SALWriter = logevent_endUnloadFilterDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample logevent_endUnloadFilter] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "logevent_endUnloadFilterDataWriter.write");

	  return status;
	}


	public int getSample(camera.logevent_endUnloadFilter data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          logevent_endUnloadFilterSeqHolder SALInstance = new logevent_endUnloadFilterSeqHolder();
	  int actorIdx = SAL__camera_logevent_endUnloadFilter_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  logevent_endUnloadFilterDataReader SALReader = logevent_endUnloadFilterDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample logevent_endUnloadFilter ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.logevent_endUnloadFilter data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_logevent_endUnloadFilter_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.logevent_endUnloadFilter data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_logevent_endUnloadFilter_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.logevent_notReadyToTakeImage data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_logevent_notReadyToTakeImage_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  logevent_notReadyToTakeImageDataWriter SALWriter = logevent_notReadyToTakeImageDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample logevent_notReadyToTakeImage] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "logevent_notReadyToTakeImageDataWriter.write");

	  return status;
	}


	public int getSample(camera.logevent_notReadyToTakeImage data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          logevent_notReadyToTakeImageSeqHolder SALInstance = new logevent_notReadyToTakeImageSeqHolder();
	  int actorIdx = SAL__camera_logevent_notReadyToTakeImage_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  logevent_notReadyToTakeImageDataReader SALReader = logevent_notReadyToTakeImageDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample logevent_notReadyToTakeImage ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.logevent_notReadyToTakeImage data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_logevent_notReadyToTakeImage_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.logevent_notReadyToTakeImage data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_logevent_notReadyToTakeImage_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.logevent_prepareToTakeImage data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_logevent_prepareToTakeImage_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  logevent_prepareToTakeImageDataWriter SALWriter = logevent_prepareToTakeImageDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample logevent_prepareToTakeImage] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "logevent_prepareToTakeImageDataWriter.write");

	  return status;
	}


	public int getSample(camera.logevent_prepareToTakeImage data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          logevent_prepareToTakeImageSeqHolder SALInstance = new logevent_prepareToTakeImageSeqHolder();
	  int actorIdx = SAL__camera_logevent_prepareToTakeImage_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  logevent_prepareToTakeImageDataReader SALReader = logevent_prepareToTakeImageDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample logevent_prepareToTakeImage ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.logevent_prepareToTakeImage data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_logevent_prepareToTakeImage_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.logevent_prepareToTakeImage data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_logevent_prepareToTakeImage_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.logevent_readyToTakeImage data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_logevent_readyToTakeImage_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  logevent_readyToTakeImageDataWriter SALWriter = logevent_readyToTakeImageDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample logevent_readyToTakeImage] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "logevent_readyToTakeImageDataWriter.write");

	  return status;
	}


	public int getSample(camera.logevent_readyToTakeImage data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          logevent_readyToTakeImageSeqHolder SALInstance = new logevent_readyToTakeImageSeqHolder();
	  int actorIdx = SAL__camera_logevent_readyToTakeImage_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  logevent_readyToTakeImageDataReader SALReader = logevent_readyToTakeImageDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample logevent_readyToTakeImage ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.logevent_readyToTakeImage data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_logevent_readyToTakeImage_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.logevent_readyToTakeImage data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_logevent_readyToTakeImage_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.logevent_startIntegration data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_logevent_startIntegration_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  logevent_startIntegrationDataWriter SALWriter = logevent_startIntegrationDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample logevent_startIntegration] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "logevent_startIntegrationDataWriter.write");

	  return status;
	}


	public int getSample(camera.logevent_startIntegration data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          logevent_startIntegrationSeqHolder SALInstance = new logevent_startIntegrationSeqHolder();
	  int actorIdx = SAL__camera_logevent_startIntegration_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  logevent_startIntegrationDataReader SALReader = logevent_startIntegrationDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample logevent_startIntegration ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.logevent_startIntegration data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_logevent_startIntegration_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.logevent_startIntegration data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_logevent_startIntegration_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.logevent_startLoadFilter data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_logevent_startLoadFilter_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  logevent_startLoadFilterDataWriter SALWriter = logevent_startLoadFilterDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample logevent_startLoadFilter] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "logevent_startLoadFilterDataWriter.write");

	  return status;
	}


	public int getSample(camera.logevent_startLoadFilter data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          logevent_startLoadFilterSeqHolder SALInstance = new logevent_startLoadFilterSeqHolder();
	  int actorIdx = SAL__camera_logevent_startLoadFilter_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  logevent_startLoadFilterDataReader SALReader = logevent_startLoadFilterDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample logevent_startLoadFilter ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.logevent_startLoadFilter data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_logevent_startLoadFilter_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.logevent_startLoadFilter data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_logevent_startLoadFilter_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.logevent_startReadout data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_logevent_startReadout_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  logevent_startReadoutDataWriter SALWriter = logevent_startReadoutDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample logevent_startReadout] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "logevent_startReadoutDataWriter.write");

	  return status;
	}


	public int getSample(camera.logevent_startReadout data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          logevent_startReadoutSeqHolder SALInstance = new logevent_startReadoutSeqHolder();
	  int actorIdx = SAL__camera_logevent_startReadout_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  logevent_startReadoutDataReader SALReader = logevent_startReadoutDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample logevent_startReadout ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.logevent_startReadout data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_logevent_startReadout_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.logevent_startReadout data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_logevent_startReadout_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.logevent_startRotateCarousel data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_logevent_startRotateCarousel_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  logevent_startRotateCarouselDataWriter SALWriter = logevent_startRotateCarouselDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample logevent_startRotateCarousel] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "logevent_startRotateCarouselDataWriter.write");

	  return status;
	}


	public int getSample(camera.logevent_startRotateCarousel data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          logevent_startRotateCarouselSeqHolder SALInstance = new logevent_startRotateCarouselSeqHolder();
	  int actorIdx = SAL__camera_logevent_startRotateCarousel_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  logevent_startRotateCarouselDataReader SALReader = logevent_startRotateCarouselDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample logevent_startRotateCarousel ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.logevent_startRotateCarousel data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_logevent_startRotateCarousel_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.logevent_startRotateCarousel data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_logevent_startRotateCarousel_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.logevent_startSetFilter data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_logevent_startSetFilter_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  logevent_startSetFilterDataWriter SALWriter = logevent_startSetFilterDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample logevent_startSetFilter] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "logevent_startSetFilterDataWriter.write");

	  return status;
	}


	public int getSample(camera.logevent_startSetFilter data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          logevent_startSetFilterSeqHolder SALInstance = new logevent_startSetFilterSeqHolder();
	  int actorIdx = SAL__camera_logevent_startSetFilter_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  logevent_startSetFilterDataReader SALReader = logevent_startSetFilterDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample logevent_startSetFilter ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.logevent_startSetFilter data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_logevent_startSetFilter_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.logevent_startSetFilter data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_logevent_startSetFilter_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.logevent_startShutterClose data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_logevent_startShutterClose_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  logevent_startShutterCloseDataWriter SALWriter = logevent_startShutterCloseDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample logevent_startShutterClose] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "logevent_startShutterCloseDataWriter.write");

	  return status;
	}


	public int getSample(camera.logevent_startShutterClose data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          logevent_startShutterCloseSeqHolder SALInstance = new logevent_startShutterCloseSeqHolder();
	  int actorIdx = SAL__camera_logevent_startShutterClose_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  logevent_startShutterCloseDataReader SALReader = logevent_startShutterCloseDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample logevent_startShutterClose ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.logevent_startShutterClose data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_logevent_startShutterClose_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.logevent_startShutterClose data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_logevent_startShutterClose_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.logevent_startShutterOpen data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_logevent_startShutterOpen_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  logevent_startShutterOpenDataWriter SALWriter = logevent_startShutterOpenDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample logevent_startShutterOpen] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "logevent_startShutterOpenDataWriter.write");

	  return status;
	}


	public int getSample(camera.logevent_startShutterOpen data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          logevent_startShutterOpenSeqHolder SALInstance = new logevent_startShutterOpenSeqHolder();
	  int actorIdx = SAL__camera_logevent_startShutterOpen_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  logevent_startShutterOpenDataReader SALReader = logevent_startShutterOpenDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample logevent_startShutterOpen ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.logevent_startShutterOpen data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_logevent_startShutterOpen_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.logevent_startShutterOpen data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_logevent_startShutterOpen_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.logevent_startUnloadFilter data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_logevent_startUnloadFilter_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  logevent_startUnloadFilterDataWriter SALWriter = logevent_startUnloadFilterDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample logevent_startUnloadFilter] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "logevent_startUnloadFilterDataWriter.write");

	  return status;
	}


	public int getSample(camera.logevent_startUnloadFilter data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          logevent_startUnloadFilterSeqHolder SALInstance = new logevent_startUnloadFilterSeqHolder();
	  int actorIdx = SAL__camera_logevent_startUnloadFilter_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  logevent_startUnloadFilterDataReader SALReader = logevent_startUnloadFilterDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample logevent_startUnloadFilter ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.logevent_startUnloadFilter data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_logevent_startUnloadFilter_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.logevent_startUnloadFilter data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_logevent_startUnloadFilter_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.command data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_command_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  commandDataWriter SALWriter = commandDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample command] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "commandDataWriter.write");

	  return status;
	}


	public int getSample(camera.command data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          commandSeqHolder SALInstance = new commandSeqHolder();
	  int actorIdx = SAL__camera_command_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  commandDataReader SALReader = commandDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample command ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.command data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_command_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.command data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_command_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.ackcmd data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_ackcmd_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  ackcmdDataWriter SALWriter = ackcmdDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample ackcmd] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "ackcmdDataWriter.write");

	  return status;
	}


	public int getSample(camera.ackcmd data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          ackcmdSeqHolder SALInstance = new ackcmdSeqHolder();
	  int actorIdx = SAL__camera_ackcmd_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  ackcmdDataReader SALReader = ackcmdDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample ackcmd ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.ackcmd data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_ackcmd_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.ackcmd data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_ackcmd_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int putSample(camera.logevent data)
	{
          int status = SAL__OK;
	  int actorIdx = SAL__camera_logevent_ACTOR;
	  if ( sal[actorIdx].isWriter == false ) {
	    createWriter(actorIdx,false);
	    sal[actorIdx].isWriter = true;
	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  logeventDataWriter SALWriter = logeventDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
          data.private_sndStamp = getCurrentTime();
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample logevent] writing a message containing :");
	    System.out.println("    revCode  : " + data.private_revCode);
	  }

           long dataHandle = HANDLE_NIL.value;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, "logeventDataWriter.write");

	  return status;
	}


	public int getSample(camera.logevent data)
	{
	  int status =  -1;
          int last = 0;
          int numsamp;
          logeventSeqHolder SALInstance = new logeventSeqHolder();
	  int actorIdx = SAL__camera_logevent_ACTOR;
	  if ( sal[actorIdx].isReader == false ) {
	    createReader(actorIdx,false);

	    sal[actorIdx].isReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  logeventDataReader SALReader = logeventDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, sal[actorIdx].maxSamples,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ALIVE_INSTANCE_STATE.value);
          numsamp = SALInstance.value.length;
          if (numsamp > 0) {
 	    if (debugLevel > 0) {
		for (int i = 0; i < numsamp; i++) {
				System.out.println("=== [getSample logevent ] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i+1;
		}
	    }
            if (last > 0) {
    		double rcvdTime = getCurrentTime();
		double dTime = rcvdTime - SALInstance.value[0].private_sndStamp;
    		if ( dTime < sal[actorIdx].sampleAge ) {
                   data = SALInstance.value[last-1];
                   last = SAL__OK;
                } else {
                   last = SAL__NO_UPDATES;
                }
            }
          } else {
              last = SAL__NO_UPDATES;
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	}

	public int getNextSample(camera.logevent data)
	{
	  int status = -1;
	  int actorIdx = SAL__camera_logevent_ACTOR;
          sal[actorIdx].maxSamples = 1;
          status = getSample(data);
          return status;
	}

	public int flushSamples(camera.logevent data)
	{
          int status = -1;
	  int actorIdx = SAL__camera_logevent_ACTOR;
          sal[actorIdx].maxSamples = DDS.LENGTH_UNLIMITED.value;
          sal[actorIdx].sampleAge = -1.0;
          status = getSample(data);
          sal[actorIdx].sampleAge = 100.0;
          return SAL__OK;
	}



	public int issueCommand_configure( command_configure data )
	{
          Random randGen = new java.util.Random();
  	  long cmdHandle = HANDLE_NIL.value;
          int status;
          int actorIdx = SAL__camera_command_configure_ACTOR;
	  if (sal[actorIdx].isCommand == false) {
	     salCommand(sal[actorIdx].topicName);
	     sal[actorIdx].isCommand = true;
	     sal[actorIdx].sndSeqNum = (int)randGen.nextInt(99999999);
	  }
	  DataWriter dwriter = getWriter(actorIdx);	
	  command_configureDataWriter SALWriter = command_configureDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST COMMAND";
	  data.private_seqNum = sal[actorIdx].sndSeqNum;
          data.private_sndStamp = getCurrentTime();
	  SALWriter.register_instance(data);

	  if (debugLevel > 0) {
	    System.out.println( "=== [issueCommand] configure writing a command containing :");
	    System.out.println( data.device + "." + data.property + "." + data.action + " : " + data.value);
	  }
	  status = SALWriter.write(data, cmdHandle);
	  sal[actorIdx].sndSeqNum++;
	  return (sal[actorIdx].sndSeqNum-1);
	}


	public int acceptCommand_configure( camera.command_configure data )
	{
                command_configureSeqHolder aCmd = new command_configureSeqHolder();
   		SampleInfoSeqHolder info;
   		int status = 0;
   		int istatus =  -1;
   		camera.ackcmd ackdata;
   		long ackHandle = HANDLE_NIL.value;
                int actorIdx = SAL__camera_command_configure_ACTOR;

  		// create DataWriter :
  		if (sal[actorIdx].isProcessor == false) {
     			salProcessor(sal[actorIdx].topicName);
     			sal[actorIdx].isProcessor = true;
  		}
  		DataWriter dwriter = getWriter2(SAL__camera_ackcmd_ACTOR);
  		ackcmdDataWriter SALWriter = ackcmdDataWriterHelper.narrow(dwriter);
  		DataReader dreader = getReader(actorIdx);
  		command_configureDataReader SALReader = command_configureDataReaderHelper.narrow(dreader);
                info = new SampleInfoSeqHolder();
  		istatus = SALReader.take(aCmd, info, 1,ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value, ANY_INSTANCE_STATE.value);
		if (aCmd.value.length > 0) {
   		  if (info.value[0].valid_data) {
    		     if (debugLevel > 8) {
      			System.out.println(  "=== [acceptCommand] configure reading a command containing :" );
      			System.out.println(  "    seqNum   : " + aCmd.value[0].private_seqNum );
      			System.out.println(  "    device   : " + aCmd.value[0].device);
      			System.out.println(  "    property : " + aCmd.value[0].property);
      			System.out.println(  "    action   : " + aCmd.value[0].action);
      			System.out.println(  "    value    : " + aCmd.value[0].value);
    		    }
    		    status = aCmd.value[0].private_seqNum;
    		    double rcvdTime = getCurrentTime();
		    double dTime = rcvdTime - aCmd.value[0].private_sndStamp;
    		    if ( dTime < sal[actorIdx].sampleAge ) {
                      ackdata = new camera.ackcmd();
		      ackdata.private_origin = aCmd.value[0].private_origin;
		      ackdata.private_seqNum = aCmd.value[0].private_seqNum;
		      ackdata.error  = 0;
		      ackdata.result = "SAL ACK";
                      data.device    = aCmd.value[0].device;
                      data.property  = aCmd.value[0].property;
                      data.action    = aCmd.value[0].action;
                      data.value     = aCmd.value[0].value;
                      data.specId = aCmd.value[0].specId;

		      status = aCmd.value[0].private_seqNum;
		      rcvSeqNum = status;
		      rcvOrigin = aCmd.value[0].private_origin;
		      ackdata.ack = SAL__CMD_ACK;

		      istatus = SALWriter.write(ackdata, ackHandle);
		      SALWriter.unregister_instance(ackdata, ackHandle);
  } else {
    		     if (debugLevel > 8) {
      			System.out.println(  "    Old command ignored :   " + dTime );
                     }
                   }
		 }
                } else {
  	           status = 0;
                }
                SALReader.return_loan(aCmd, info);
	        return status;
	}


	public int waitForCompletion_configure( int cmdSeqNum , int timeout )
	{
	   int status = 0;
	   int countdown = timeout*1000;
           int actorIdx = SAL__camera_command_configure_ACTOR;
	   ackcmdSeqHolder ackcmd = new ackcmdSeqHolder();

	   while (status != SAL__CMD_COMPLETE && countdown != 0) {
	      status = getResponse_configure(ackcmd);
	      if (status != SAL__CMD_NOACK) {
	        if (sal[actorIdx].rcvSeqNum != cmdSeqNum) { 
	           status = SAL__CMD_NOACK;
	        }
	      }
	      try
		{
	 	  Thread.sleep(timeout);
		}
		catch(InterruptedException ie)
		{
			// nothing to do
	      }
	      countdown--;
	   }
	   if (status != SAL__CMD_COMPLETE) {
	      if (debugLevel > 0) {
	         System.out.println( "=== [waitForCompletion_configure] command " + cmdSeqNum +  " timed out");
	      } 
	      logError(status);
	   } else {
	      if (debugLevel > 0) {
	         System.out.println( "=== [waitForCompletion_configure] command " + cmdSeqNum +  " completed ok");
	      } 
           }
 	   return status;
	}


	public int getResponse_configure(ackcmdSeqHolder data)
	{
	  int status =  -1;
          int lastsample = 0;
          int actorIdx = SAL__camera_ackcmd_ACTOR;
          int actorIdxCmd = SAL__camera_command_configure_ACTOR;

	  DataReader dreader = getReader2(actorIdx);
	  ackcmdDataReader SALReader = ackcmdDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(data, infoSeq, 1, 
					ANY_SAMPLE_STATE.value,
					ANY_VIEW_STATE.value,
					ANY_INSTANCE_STATE.value);
	  if (data.value.length > 0) {
 		for (int i = 0; i < data.value.length; i++) {
                     if ( debugLevel > 8) {
				System.out.println("=== [getResponse_configure] message received :");
				System.out.println("    revCode  : "
						+ data.value[i].private_revCode);
		    }
                    lastsample = i;
		}
	 	status = data.value[lastsample].ack;
	  	sal[actorIdxCmd].rcvSeqNum = data.value[lastsample].private_seqNum;
	  	sal[actorIdxCmd].rcvOrigin = data.value[lastsample].private_origin;
	  } else {
                if ( debugLevel > 8) {
	            System.out.println("=== [getResponse_configure] No ack yet!"); 
                }
	        status = SAL__CMD_NOACK;
	  }
    	  SALReader.return_loan(data, infoSeq);
	  return status;
	}


	public int ackCommand_configure( int cmdId, int ack, int error, String result )
	{
   		int istatus = -1;
   		long ackHandle = HANDLE_NIL.value;
                int actorIdx = SAL__camera_command_configure_ACTOR;
                int actorIdx2 = SAL__camera_ackcmd_ACTOR;

   		camera.ackcmd ackdata;
   		DataWriter dwriter = getWriter2(actorIdx2);
   		ackcmdDataWriter SALWriter = ackcmdDataWriterHelper.narrow(dwriter);
                ackdata = new camera.ackcmd();
   		ackdata.private_origin = sal[actorIdx].rcvOrigin;
   		ackdata.private_seqNum = cmdId;
   		ackdata.error = error;
   		ackdata.ack = ack;
   		ackdata.result = result;

   		if (debugLevel > 0) {
      			System.out.println(  "=== [ackCommand_configure] acknowledging a command with :" );
      			System.out.println(  "    seqNum   : " + ackdata.private_seqNum );
      			System.out.println(  "    ack      : " + ackdata.ack );
      			System.out.println(  "    error    : " + ackdata.error );
      			System.out.println(  "    result   : " + ackdata.result );
   		}
   		istatus = SALWriter.write(ackdata, ackHandle);
    		SALWriter.unregister_instance(ackdata, ackHandle);

   		return SAL__OK;
	}


	public int issueCommand_initGuiders( command_initGuiders data )
	{
          Random randGen = new java.util.Random();
  	  long cmdHandle = HANDLE_NIL.value;
          int status;
          int actorIdx = SAL__camera_command_initGuiders_ACTOR;
	  if (sal[actorIdx].isCommand == false) {
	     salCommand(sal[actorIdx].topicName);
	     sal[actorIdx].isCommand = true;
	     sal[actorIdx].sndSeqNum = (int)randGen.nextInt(99999999);
	  }
	  DataWriter dwriter = getWriter(actorIdx);	
	  command_initGuidersDataWriter SALWriter = command_initGuidersDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST COMMAND";
	  data.private_seqNum = sal[actorIdx].sndSeqNum;
          data.private_sndStamp = getCurrentTime();
	  SALWriter.register_instance(data);

	  if (debugLevel > 0) {
	    System.out.println( "=== [issueCommand] initGuiders writing a command containing :");
	    System.out.println( data.device + "." + data.property + "." + data.action + " : " + data.value);
	  }
	  status = SALWriter.write(data, cmdHandle);
	  sal[actorIdx].sndSeqNum++;
	  return (sal[actorIdx].sndSeqNum-1);
	}


	public int acceptCommand_initGuiders( camera.command_initGuiders data )
	{
                command_initGuidersSeqHolder aCmd = new command_initGuidersSeqHolder();
   		SampleInfoSeqHolder info;
   		int status = 0;
   		int istatus =  -1;
   		camera.ackcmd ackdata;
   		long ackHandle = HANDLE_NIL.value;
                int actorIdx = SAL__camera_command_initGuiders_ACTOR;

  		// create DataWriter :
  		if (sal[actorIdx].isProcessor == false) {
     			salProcessor(sal[actorIdx].topicName);
     			sal[actorIdx].isProcessor = true;
  		}
  		DataWriter dwriter = getWriter2(SAL__camera_ackcmd_ACTOR);
  		ackcmdDataWriter SALWriter = ackcmdDataWriterHelper.narrow(dwriter);
  		DataReader dreader = getReader(actorIdx);
  		command_initGuidersDataReader SALReader = command_initGuidersDataReaderHelper.narrow(dreader);
                info = new SampleInfoSeqHolder();
  		istatus = SALReader.take(aCmd, info, 1,ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value, ANY_INSTANCE_STATE.value);
		if (aCmd.value.length > 0) {
   		  if (info.value[0].valid_data) {
    		     if (debugLevel > 8) {
      			System.out.println(  "=== [acceptCommand] initGuiders reading a command containing :" );
      			System.out.println(  "    seqNum   : " + aCmd.value[0].private_seqNum );
      			System.out.println(  "    device   : " + aCmd.value[0].device);
      			System.out.println(  "    property : " + aCmd.value[0].property);
      			System.out.println(  "    action   : " + aCmd.value[0].action);
      			System.out.println(  "    value    : " + aCmd.value[0].value);
    		    }
    		    status = aCmd.value[0].private_seqNum;
    		    double rcvdTime = getCurrentTime();
		    double dTime = rcvdTime - aCmd.value[0].private_sndStamp;
    		    if ( dTime < sal[actorIdx].sampleAge ) {
                      ackdata = new camera.ackcmd();
		      ackdata.private_origin = aCmd.value[0].private_origin;
		      ackdata.private_seqNum = aCmd.value[0].private_seqNum;
		      ackdata.error  = 0;
		      ackdata.result = "SAL ACK";
                      data.device    = aCmd.value[0].device;
                      data.property  = aCmd.value[0].property;
                      data.action    = aCmd.value[0].action;
                      data.value     = aCmd.value[0].value;
                      data.roiSpec = aCmd.value[0].roiSpec;

		      status = aCmd.value[0].private_seqNum;
		      rcvSeqNum = status;
		      rcvOrigin = aCmd.value[0].private_origin;
		      ackdata.ack = SAL__CMD_ACK;

		      istatus = SALWriter.write(ackdata, ackHandle);
		      SALWriter.unregister_instance(ackdata, ackHandle);
  } else {
    		     if (debugLevel > 8) {
      			System.out.println(  "    Old command ignored :   " + dTime );
                     }
                   }
		 }
                } else {
  	           status = 0;
                }
                SALReader.return_loan(aCmd, info);
	        return status;
	}


	public int waitForCompletion_initGuiders( int cmdSeqNum , int timeout )
	{
	   int status = 0;
	   int countdown = timeout*1000;
           int actorIdx = SAL__camera_command_initGuiders_ACTOR;
	   ackcmdSeqHolder ackcmd = new ackcmdSeqHolder();

	   while (status != SAL__CMD_COMPLETE && countdown != 0) {
	      status = getResponse_initGuiders(ackcmd);
	      if (status != SAL__CMD_NOACK) {
	        if (sal[actorIdx].rcvSeqNum != cmdSeqNum) { 
	           status = SAL__CMD_NOACK;
	        }
	      }
	      try
		{
	 	  Thread.sleep(timeout);
		}
		catch(InterruptedException ie)
		{
			// nothing to do
	      }
	      countdown--;
	   }
	   if (status != SAL__CMD_COMPLETE) {
	      if (debugLevel > 0) {
	         System.out.println( "=== [waitForCompletion_initGuiders] command " + cmdSeqNum +  " timed out");
	      } 
	      logError(status);
	   } else {
	      if (debugLevel > 0) {
	         System.out.println( "=== [waitForCompletion_initGuiders] command " + cmdSeqNum +  " completed ok");
	      } 
           }
 	   return status;
	}


	public int getResponse_initGuiders(ackcmdSeqHolder data)
	{
	  int status =  -1;
          int lastsample = 0;
          int actorIdx = SAL__camera_ackcmd_ACTOR;
          int actorIdxCmd = SAL__camera_command_initGuiders_ACTOR;

	  DataReader dreader = getReader2(actorIdx);
	  ackcmdDataReader SALReader = ackcmdDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(data, infoSeq, 1, 
					ANY_SAMPLE_STATE.value,
					ANY_VIEW_STATE.value,
					ANY_INSTANCE_STATE.value);
	  if (data.value.length > 0) {
 		for (int i = 0; i < data.value.length; i++) {
                     if ( debugLevel > 8) {
				System.out.println("=== [getResponse_initGuiders] message received :");
				System.out.println("    revCode  : "
						+ data.value[i].private_revCode);
		    }
                    lastsample = i;
		}
	 	status = data.value[lastsample].ack;
	  	sal[actorIdxCmd].rcvSeqNum = data.value[lastsample].private_seqNum;
	  	sal[actorIdxCmd].rcvOrigin = data.value[lastsample].private_origin;
	  } else {
                if ( debugLevel > 8) {
	            System.out.println("=== [getResponse_initGuiders] No ack yet!"); 
                }
	        status = SAL__CMD_NOACK;
	  }
    	  SALReader.return_loan(data, infoSeq);
	  return status;
	}


	public int ackCommand_initGuiders( int cmdId, int ack, int error, String result )
	{
   		int istatus = -1;
   		long ackHandle = HANDLE_NIL.value;
                int actorIdx = SAL__camera_command_initGuiders_ACTOR;
                int actorIdx2 = SAL__camera_ackcmd_ACTOR;

   		camera.ackcmd ackdata;
   		DataWriter dwriter = getWriter2(actorIdx2);
   		ackcmdDataWriter SALWriter = ackcmdDataWriterHelper.narrow(dwriter);
                ackdata = new camera.ackcmd();
   		ackdata.private_origin = sal[actorIdx].rcvOrigin;
   		ackdata.private_seqNum = cmdId;
   		ackdata.error = error;
   		ackdata.ack = ack;
   		ackdata.result = result;

   		if (debugLevel > 0) {
      			System.out.println(  "=== [ackCommand_initGuiders] acknowledging a command with :" );
      			System.out.println(  "    seqNum   : " + ackdata.private_seqNum );
      			System.out.println(  "    ack      : " + ackdata.ack );
      			System.out.println(  "    error    : " + ackdata.error );
      			System.out.println(  "    result   : " + ackdata.result );
   		}
   		istatus = SALWriter.write(ackdata, ackHandle);
    		SALWriter.unregister_instance(ackdata, ackHandle);

   		return SAL__OK;
	}


	public int issueCommand_initImage( command_initImage data )
	{
          Random randGen = new java.util.Random();
  	  long cmdHandle = HANDLE_NIL.value;
          int status;
          int actorIdx = SAL__camera_command_initImage_ACTOR;
	  if (sal[actorIdx].isCommand == false) {
	     salCommand(sal[actorIdx].topicName);
	     sal[actorIdx].isCommand = true;
	     sal[actorIdx].sndSeqNum = (int)randGen.nextInt(99999999);
	  }
	  DataWriter dwriter = getWriter(actorIdx);	
	  command_initImageDataWriter SALWriter = command_initImageDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST COMMAND";
	  data.private_seqNum = sal[actorIdx].sndSeqNum;
          data.private_sndStamp = getCurrentTime();
	  SALWriter.register_instance(data);

	  if (debugLevel > 0) {
	    System.out.println( "=== [issueCommand] initImage writing a command containing :");
	    System.out.println( data.device + "." + data.property + "." + data.action + " : " + data.value);
	  }
	  status = SALWriter.write(data, cmdHandle);
	  sal[actorIdx].sndSeqNum++;
	  return (sal[actorIdx].sndSeqNum-1);
	}


	public int acceptCommand_initImage( camera.command_initImage data )
	{
                command_initImageSeqHolder aCmd = new command_initImageSeqHolder();
   		SampleInfoSeqHolder info;
   		int status = 0;
   		int istatus =  -1;
   		camera.ackcmd ackdata;
   		long ackHandle = HANDLE_NIL.value;
                int actorIdx = SAL__camera_command_initImage_ACTOR;

  		// create DataWriter :
  		if (sal[actorIdx].isProcessor == false) {
     			salProcessor(sal[actorIdx].topicName);
     			sal[actorIdx].isProcessor = true;
  		}
  		DataWriter dwriter = getWriter2(SAL__camera_ackcmd_ACTOR);
  		ackcmdDataWriter SALWriter = ackcmdDataWriterHelper.narrow(dwriter);
  		DataReader dreader = getReader(actorIdx);
  		command_initImageDataReader SALReader = command_initImageDataReaderHelper.narrow(dreader);
                info = new SampleInfoSeqHolder();
  		istatus = SALReader.take(aCmd, info, 1,ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value, ANY_INSTANCE_STATE.value);
		if (aCmd.value.length > 0) {
   		  if (info.value[0].valid_data) {
    		     if (debugLevel > 8) {
      			System.out.println(  "=== [acceptCommand] initImage reading a command containing :" );
      			System.out.println(  "    seqNum   : " + aCmd.value[0].private_seqNum );
      			System.out.println(  "    device   : " + aCmd.value[0].device);
      			System.out.println(  "    property : " + aCmd.value[0].property);
      			System.out.println(  "    action   : " + aCmd.value[0].action);
      			System.out.println(  "    value    : " + aCmd.value[0].value);
    		    }
    		    status = aCmd.value[0].private_seqNum;
    		    double rcvdTime = getCurrentTime();
		    double dTime = rcvdTime - aCmd.value[0].private_sndStamp;
    		    if ( dTime < sal[actorIdx].sampleAge ) {
                      ackdata = new camera.ackcmd();
		      ackdata.private_origin = aCmd.value[0].private_origin;
		      ackdata.private_seqNum = aCmd.value[0].private_seqNum;
		      ackdata.error  = 0;
		      ackdata.result = "SAL ACK";
                      data.device    = aCmd.value[0].device;
                      data.property  = aCmd.value[0].property;
                      data.action    = aCmd.value[0].action;
                      data.value     = aCmd.value[0].value;
                      data.deltaT = aCmd.value[0].deltaT;

		      status = aCmd.value[0].private_seqNum;
		      rcvSeqNum = status;
		      rcvOrigin = aCmd.value[0].private_origin;
		      ackdata.ack = SAL__CMD_ACK;

		      istatus = SALWriter.write(ackdata, ackHandle);
		      SALWriter.unregister_instance(ackdata, ackHandle);
  } else {
    		     if (debugLevel > 8) {
      			System.out.println(  "    Old command ignored :   " + dTime );
                     }
                   }
		 }
                } else {
  	           status = 0;
                }
                SALReader.return_loan(aCmd, info);
	        return status;
	}


	public int waitForCompletion_initImage( int cmdSeqNum , int timeout )
	{
	   int status = 0;
	   int countdown = timeout*1000;
           int actorIdx = SAL__camera_command_initImage_ACTOR;
	   ackcmdSeqHolder ackcmd = new ackcmdSeqHolder();

	   while (status != SAL__CMD_COMPLETE && countdown != 0) {
	      status = getResponse_initImage(ackcmd);
	      if (status != SAL__CMD_NOACK) {
	        if (sal[actorIdx].rcvSeqNum != cmdSeqNum) { 
	           status = SAL__CMD_NOACK;
	        }
	      }
	      try
		{
	 	  Thread.sleep(timeout);
		}
		catch(InterruptedException ie)
		{
			// nothing to do
	      }
	      countdown--;
	   }
	   if (status != SAL__CMD_COMPLETE) {
	      if (debugLevel > 0) {
	         System.out.println( "=== [waitForCompletion_initImage] command " + cmdSeqNum +  " timed out");
	      } 
	      logError(status);
	   } else {
	      if (debugLevel > 0) {
	         System.out.println( "=== [waitForCompletion_initImage] command " + cmdSeqNum +  " completed ok");
	      } 
           }
 	   return status;
	}


	public int getResponse_initImage(ackcmdSeqHolder data)
	{
	  int status =  -1;
          int lastsample = 0;
          int actorIdx = SAL__camera_ackcmd_ACTOR;
          int actorIdxCmd = SAL__camera_command_initImage_ACTOR;

	  DataReader dreader = getReader2(actorIdx);
	  ackcmdDataReader SALReader = ackcmdDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(data, infoSeq, 1, 
					ANY_SAMPLE_STATE.value,
					ANY_VIEW_STATE.value,
					ANY_INSTANCE_STATE.value);
	  if (data.value.length > 0) {
 		for (int i = 0; i < data.value.length; i++) {
                     if ( debugLevel > 8) {
				System.out.println("=== [getResponse_initImage] message received :");
				System.out.println("    revCode  : "
						+ data.value[i].private_revCode);
		    }
                    lastsample = i;
		}
	 	status = data.value[lastsample].ack;
	  	sal[actorIdxCmd].rcvSeqNum = data.value[lastsample].private_seqNum;
	  	sal[actorIdxCmd].rcvOrigin = data.value[lastsample].private_origin;
	  } else {
                if ( debugLevel > 8) {
	            System.out.println("=== [getResponse_initImage] No ack yet!"); 
                }
	        status = SAL__CMD_NOACK;
	  }
    	  SALReader.return_loan(data, infoSeq);
	  return status;
	}


	public int ackCommand_initImage( int cmdId, int ack, int error, String result )
	{
   		int istatus = -1;
   		long ackHandle = HANDLE_NIL.value;
                int actorIdx = SAL__camera_command_initImage_ACTOR;
                int actorIdx2 = SAL__camera_ackcmd_ACTOR;

   		camera.ackcmd ackdata;
   		DataWriter dwriter = getWriter2(actorIdx2);
   		ackcmdDataWriter SALWriter = ackcmdDataWriterHelper.narrow(dwriter);
                ackdata = new camera.ackcmd();
   		ackdata.private_origin = sal[actorIdx].rcvOrigin;
   		ackdata.private_seqNum = cmdId;
   		ackdata.error = error;
   		ackdata.ack = ack;
   		ackdata.result = result;

   		if (debugLevel > 0) {
      			System.out.println(  "=== [ackCommand_initImage] acknowledging a command with :" );
      			System.out.println(  "    seqNum   : " + ackdata.private_seqNum );
      			System.out.println(  "    ack      : " + ackdata.ack );
      			System.out.println(  "    error    : " + ackdata.error );
      			System.out.println(  "    result   : " + ackdata.result );
   		}
   		istatus = SALWriter.write(ackdata, ackHandle);
    		SALWriter.unregister_instance(ackdata, ackHandle);

   		return SAL__OK;
	}


	public int issueCommand_setFilter( command_setFilter data )
	{
          Random randGen = new java.util.Random();
  	  long cmdHandle = HANDLE_NIL.value;
          int status;
          int actorIdx = SAL__camera_command_setFilter_ACTOR;
	  if (sal[actorIdx].isCommand == false) {
	     salCommand(sal[actorIdx].topicName);
	     sal[actorIdx].isCommand = true;
	     sal[actorIdx].sndSeqNum = (int)randGen.nextInt(99999999);
	  }
	  DataWriter dwriter = getWriter(actorIdx);	
	  command_setFilterDataWriter SALWriter = command_setFilterDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST COMMAND";
	  data.private_seqNum = sal[actorIdx].sndSeqNum;
          data.private_sndStamp = getCurrentTime();
	  SALWriter.register_instance(data);

	  if (debugLevel > 0) {
	    System.out.println( "=== [issueCommand] setFilter writing a command containing :");
	    System.out.println( data.device + "." + data.property + "." + data.action + " : " + data.value);
	  }
	  status = SALWriter.write(data, cmdHandle);
	  sal[actorIdx].sndSeqNum++;
	  return (sal[actorIdx].sndSeqNum-1);
	}


	public int acceptCommand_setFilter( camera.command_setFilter data )
	{
                command_setFilterSeqHolder aCmd = new command_setFilterSeqHolder();
   		SampleInfoSeqHolder info;
   		int status = 0;
   		int istatus =  -1;
   		camera.ackcmd ackdata;
   		long ackHandle = HANDLE_NIL.value;
                int actorIdx = SAL__camera_command_setFilter_ACTOR;

  		// create DataWriter :
  		if (sal[actorIdx].isProcessor == false) {
     			salProcessor(sal[actorIdx].topicName);
     			sal[actorIdx].isProcessor = true;
  		}
  		DataWriter dwriter = getWriter2(SAL__camera_ackcmd_ACTOR);
  		ackcmdDataWriter SALWriter = ackcmdDataWriterHelper.narrow(dwriter);
  		DataReader dreader = getReader(actorIdx);
  		command_setFilterDataReader SALReader = command_setFilterDataReaderHelper.narrow(dreader);
                info = new SampleInfoSeqHolder();
  		istatus = SALReader.take(aCmd, info, 1,ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value, ANY_INSTANCE_STATE.value);
		if (aCmd.value.length > 0) {
   		  if (info.value[0].valid_data) {
    		     if (debugLevel > 8) {
      			System.out.println(  "=== [acceptCommand] setFilter reading a command containing :" );
      			System.out.println(  "    seqNum   : " + aCmd.value[0].private_seqNum );
      			System.out.println(  "    device   : " + aCmd.value[0].device);
      			System.out.println(  "    property : " + aCmd.value[0].property);
      			System.out.println(  "    action   : " + aCmd.value[0].action);
      			System.out.println(  "    value    : " + aCmd.value[0].value);
    		    }
    		    status = aCmd.value[0].private_seqNum;
    		    double rcvdTime = getCurrentTime();
		    double dTime = rcvdTime - aCmd.value[0].private_sndStamp;
    		    if ( dTime < sal[actorIdx].sampleAge ) {
                      ackdata = new camera.ackcmd();
		      ackdata.private_origin = aCmd.value[0].private_origin;
		      ackdata.private_seqNum = aCmd.value[0].private_seqNum;
		      ackdata.error  = 0;
		      ackdata.result = "SAL ACK";
                      data.device    = aCmd.value[0].device;
                      data.property  = aCmd.value[0].property;
                      data.action    = aCmd.value[0].action;
                      data.value     = aCmd.value[0].value;
                      data.name = aCmd.value[0].name;

		      status = aCmd.value[0].private_seqNum;
		      rcvSeqNum = status;
		      rcvOrigin = aCmd.value[0].private_origin;
		      ackdata.ack = SAL__CMD_ACK;

		      istatus = SALWriter.write(ackdata, ackHandle);
		      SALWriter.unregister_instance(ackdata, ackHandle);
  } else {
    		     if (debugLevel > 8) {
      			System.out.println(  "    Old command ignored :   " + dTime );
                     }
                   }
		 }
                } else {
  	           status = 0;
                }
                SALReader.return_loan(aCmd, info);
	        return status;
	}


	public int waitForCompletion_setFilter( int cmdSeqNum , int timeout )
	{
	   int status = 0;
	   int countdown = timeout*1000;
           int actorIdx = SAL__camera_command_setFilter_ACTOR;
	   ackcmdSeqHolder ackcmd = new ackcmdSeqHolder();

	   while (status != SAL__CMD_COMPLETE && countdown != 0) {
	      status = getResponse_setFilter(ackcmd);
	      if (status != SAL__CMD_NOACK) {
	        if (sal[actorIdx].rcvSeqNum != cmdSeqNum) { 
	           status = SAL__CMD_NOACK;
	        }
	      }
	      try
		{
	 	  Thread.sleep(timeout);
		}
		catch(InterruptedException ie)
		{
			// nothing to do
	      }
	      countdown--;
	   }
	   if (status != SAL__CMD_COMPLETE) {
	      if (debugLevel > 0) {
	         System.out.println( "=== [waitForCompletion_setFilter] command " + cmdSeqNum +  " timed out");
	      } 
	      logError(status);
	   } else {
	      if (debugLevel > 0) {
	         System.out.println( "=== [waitForCompletion_setFilter] command " + cmdSeqNum +  " completed ok");
	      } 
           }
 	   return status;
	}


	public int getResponse_setFilter(ackcmdSeqHolder data)
	{
	  int status =  -1;
          int lastsample = 0;
          int actorIdx = SAL__camera_ackcmd_ACTOR;
          int actorIdxCmd = SAL__camera_command_setFilter_ACTOR;

	  DataReader dreader = getReader2(actorIdx);
	  ackcmdDataReader SALReader = ackcmdDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(data, infoSeq, 1, 
					ANY_SAMPLE_STATE.value,
					ANY_VIEW_STATE.value,
					ANY_INSTANCE_STATE.value);
	  if (data.value.length > 0) {
 		for (int i = 0; i < data.value.length; i++) {
                     if ( debugLevel > 8) {
				System.out.println("=== [getResponse_setFilter] message received :");
				System.out.println("    revCode  : "
						+ data.value[i].private_revCode);
		    }
                    lastsample = i;
		}
	 	status = data.value[lastsample].ack;
	  	sal[actorIdxCmd].rcvSeqNum = data.value[lastsample].private_seqNum;
	  	sal[actorIdxCmd].rcvOrigin = data.value[lastsample].private_origin;
	  } else {
                if ( debugLevel > 8) {
	            System.out.println("=== [getResponse_setFilter] No ack yet!"); 
                }
	        status = SAL__CMD_NOACK;
	  }
    	  SALReader.return_loan(data, infoSeq);
	  return status;
	}


	public int ackCommand_setFilter( int cmdId, int ack, int error, String result )
	{
   		int istatus = -1;
   		long ackHandle = HANDLE_NIL.value;
                int actorIdx = SAL__camera_command_setFilter_ACTOR;
                int actorIdx2 = SAL__camera_ackcmd_ACTOR;

   		camera.ackcmd ackdata;
   		DataWriter dwriter = getWriter2(actorIdx2);
   		ackcmdDataWriter SALWriter = ackcmdDataWriterHelper.narrow(dwriter);
                ackdata = new camera.ackcmd();
   		ackdata.private_origin = sal[actorIdx].rcvOrigin;
   		ackdata.private_seqNum = cmdId;
   		ackdata.error = error;
   		ackdata.ack = ack;
   		ackdata.result = result;

   		if (debugLevel > 0) {
      			System.out.println(  "=== [ackCommand_setFilter] acknowledging a command with :" );
      			System.out.println(  "    seqNum   : " + ackdata.private_seqNum );
      			System.out.println(  "    ack      : " + ackdata.ack );
      			System.out.println(  "    error    : " + ackdata.error );
      			System.out.println(  "    result   : " + ackdata.result );
   		}
   		istatus = SALWriter.write(ackdata, ackHandle);
    		SALWriter.unregister_instance(ackdata, ackHandle);

   		return SAL__OK;
	}


	public int issueCommand_takeImages( command_takeImages data )
	{
          Random randGen = new java.util.Random();
  	  long cmdHandle = HANDLE_NIL.value;
          int status;
          int actorIdx = SAL__camera_command_takeImages_ACTOR;
	  if (sal[actorIdx].isCommand == false) {
	     salCommand(sal[actorIdx].topicName);
	     sal[actorIdx].isCommand = true;
	     sal[actorIdx].sndSeqNum = (int)randGen.nextInt(99999999);
	  }
	  DataWriter dwriter = getWriter(actorIdx);	
	  command_takeImagesDataWriter SALWriter = command_takeImagesDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST COMMAND";
	  data.private_seqNum = sal[actorIdx].sndSeqNum;
          data.private_sndStamp = getCurrentTime();
	  SALWriter.register_instance(data);

	  if (debugLevel > 0) {
	    System.out.println( "=== [issueCommand] takeImages writing a command containing :");
	    System.out.println( data.device + "." + data.property + "." + data.action + " : " + data.value);
	  }
	  status = SALWriter.write(data, cmdHandle);
	  sal[actorIdx].sndSeqNum++;
	  return (sal[actorIdx].sndSeqNum-1);
	}


	public int acceptCommand_takeImages( camera.command_takeImages data )
	{
                command_takeImagesSeqHolder aCmd = new command_takeImagesSeqHolder();
   		SampleInfoSeqHolder info;
   		int status = 0;
   		int istatus =  -1;
   		camera.ackcmd ackdata;
   		long ackHandle = HANDLE_NIL.value;
                int actorIdx = SAL__camera_command_takeImages_ACTOR;

  		// create DataWriter :
  		if (sal[actorIdx].isProcessor == false) {
     			salProcessor(sal[actorIdx].topicName);
     			sal[actorIdx].isProcessor = true;
  		}
  		DataWriter dwriter = getWriter2(SAL__camera_ackcmd_ACTOR);
  		ackcmdDataWriter SALWriter = ackcmdDataWriterHelper.narrow(dwriter);
  		DataReader dreader = getReader(actorIdx);
  		command_takeImagesDataReader SALReader = command_takeImagesDataReaderHelper.narrow(dreader);
                info = new SampleInfoSeqHolder();
  		istatus = SALReader.take(aCmd, info, 1,ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value, ANY_INSTANCE_STATE.value);
		if (aCmd.value.length > 0) {
   		  if (info.value[0].valid_data) {
    		     if (debugLevel > 8) {
      			System.out.println(  "=== [acceptCommand] takeImages reading a command containing :" );
      			System.out.println(  "    seqNum   : " + aCmd.value[0].private_seqNum );
      			System.out.println(  "    device   : " + aCmd.value[0].device);
      			System.out.println(  "    property : " + aCmd.value[0].property);
      			System.out.println(  "    action   : " + aCmd.value[0].action);
      			System.out.println(  "    value    : " + aCmd.value[0].value);
    		    }
    		    status = aCmd.value[0].private_seqNum;
    		    double rcvdTime = getCurrentTime();
		    double dTime = rcvdTime - aCmd.value[0].private_sndStamp;
    		    if ( dTime < sal[actorIdx].sampleAge ) {
                      ackdata = new camera.ackcmd();
		      ackdata.private_origin = aCmd.value[0].private_origin;
		      ackdata.private_seqNum = aCmd.value[0].private_seqNum;
		      ackdata.error  = 0;
		      ackdata.result = "SAL ACK";
                      data.device    = aCmd.value[0].device;
                      data.property  = aCmd.value[0].property;
                      data.action    = aCmd.value[0].action;
                      data.value     = aCmd.value[0].value;
                      data.numImages = aCmd.value[0].numImages;
                      data.expTime = aCmd.value[0].expTime;
                      data.shutter = aCmd.value[0].shutter;
                      data.science = aCmd.value[0].science;
                      data.guide = aCmd.value[0].guide;
                      data.wfs = aCmd.value[0].wfs;
                      data.imageSequenceName = aCmd.value[0].imageSequenceName;

		      status = aCmd.value[0].private_seqNum;
		      rcvSeqNum = status;
		      rcvOrigin = aCmd.value[0].private_origin;
		      ackdata.ack = SAL__CMD_ACK;

		      istatus = SALWriter.write(ackdata, ackHandle);
		      SALWriter.unregister_instance(ackdata, ackHandle);
  } else {
    		     if (debugLevel > 8) {
      			System.out.println(  "    Old command ignored :   " + dTime );
                     }
                   }
		 }
                } else {
  	           status = 0;
                }
                SALReader.return_loan(aCmd, info);
	        return status;
	}


	public int waitForCompletion_takeImages( int cmdSeqNum , int timeout )
	{
	   int status = 0;
	   int countdown = timeout*1000;
           int actorIdx = SAL__camera_command_takeImages_ACTOR;
	   ackcmdSeqHolder ackcmd = new ackcmdSeqHolder();

	   while (status != SAL__CMD_COMPLETE && countdown != 0) {
	      status = getResponse_takeImages(ackcmd);
	      if (status != SAL__CMD_NOACK) {
	        if (sal[actorIdx].rcvSeqNum != cmdSeqNum) { 
	           status = SAL__CMD_NOACK;
	        }
	      }
	      try
		{
	 	  Thread.sleep(timeout);
		}
		catch(InterruptedException ie)
		{
			// nothing to do
	      }
	      countdown--;
	   }
	   if (status != SAL__CMD_COMPLETE) {
	      if (debugLevel > 0) {
	         System.out.println( "=== [waitForCompletion_takeImages] command " + cmdSeqNum +  " timed out");
	      } 
	      logError(status);
	   } else {
	      if (debugLevel > 0) {
	         System.out.println( "=== [waitForCompletion_takeImages] command " + cmdSeqNum +  " completed ok");
	      } 
           }
 	   return status;
	}


	public int getResponse_takeImages(ackcmdSeqHolder data)
	{
	  int status =  -1;
          int lastsample = 0;
          int actorIdx = SAL__camera_ackcmd_ACTOR;
          int actorIdxCmd = SAL__camera_command_takeImages_ACTOR;

	  DataReader dreader = getReader2(actorIdx);
	  ackcmdDataReader SALReader = ackcmdDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(data, infoSeq, 1, 
					ANY_SAMPLE_STATE.value,
					ANY_VIEW_STATE.value,
					ANY_INSTANCE_STATE.value);
	  if (data.value.length > 0) {
 		for (int i = 0; i < data.value.length; i++) {
                     if ( debugLevel > 8) {
				System.out.println("=== [getResponse_takeImages] message received :");
				System.out.println("    revCode  : "
						+ data.value[i].private_revCode);
		    }
                    lastsample = i;
		}
	 	status = data.value[lastsample].ack;
	  	sal[actorIdxCmd].rcvSeqNum = data.value[lastsample].private_seqNum;
	  	sal[actorIdxCmd].rcvOrigin = data.value[lastsample].private_origin;
	  } else {
                if ( debugLevel > 8) {
	            System.out.println("=== [getResponse_takeImages] No ack yet!"); 
                }
	        status = SAL__CMD_NOACK;
	  }
    	  SALReader.return_loan(data, infoSeq);
	  return status;
	}


	public int ackCommand_takeImages( int cmdId, int ack, int error, String result )
	{
   		int istatus = -1;
   		long ackHandle = HANDLE_NIL.value;
                int actorIdx = SAL__camera_command_takeImages_ACTOR;
                int actorIdx2 = SAL__camera_ackcmd_ACTOR;

   		camera.ackcmd ackdata;
   		DataWriter dwriter = getWriter2(actorIdx2);
   		ackcmdDataWriter SALWriter = ackcmdDataWriterHelper.narrow(dwriter);
                ackdata = new camera.ackcmd();
   		ackdata.private_origin = sal[actorIdx].rcvOrigin;
   		ackdata.private_seqNum = cmdId;
   		ackdata.error = error;
   		ackdata.ack = ack;
   		ackdata.result = result;

   		if (debugLevel > 0) {
      			System.out.println(  "=== [ackCommand_takeImages] acknowledging a command with :" );
      			System.out.println(  "    seqNum   : " + ackdata.private_seqNum );
      			System.out.println(  "    ack      : " + ackdata.ack );
      			System.out.println(  "    error    : " + ackdata.error );
      			System.out.println(  "    result   : " + ackdata.result );
   		}
   		istatus = SALWriter.write(ackdata, ackHandle);
    		SALWriter.unregister_instance(ackdata, ackHandle);

   		return SAL__OK;
	}


	public int issueCommand_start( command_start data )
	{
          Random randGen = new java.util.Random();
  	  long cmdHandle = HANDLE_NIL.value;
          int status;
          int actorIdx = SAL__camera_command_start_ACTOR;
	  if (sal[actorIdx].isCommand == false) {
	     salCommand(sal[actorIdx].topicName);
	     sal[actorIdx].isCommand = true;
	     sal[actorIdx].sndSeqNum = (int)randGen.nextInt(99999999);
	  }
	  DataWriter dwriter = getWriter(actorIdx);	
	  command_startDataWriter SALWriter = command_startDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST COMMAND";
	  data.private_seqNum = sal[actorIdx].sndSeqNum;
          data.private_sndStamp = getCurrentTime();
	  SALWriter.register_instance(data);

	  if (debugLevel > 0) {
	    System.out.println( "=== [issueCommand] start writing a command containing :");
	    System.out.println( data.device + "." + data.property + "." + data.action + " : " + data.value);
	  }
	  status = SALWriter.write(data, cmdHandle);
	  sal[actorIdx].sndSeqNum++;
	  return (sal[actorIdx].sndSeqNum-1);
	}


	public int acceptCommand_start( camera.command_start data )
	{
                command_startSeqHolder aCmd = new command_startSeqHolder();
   		SampleInfoSeqHolder info;
   		int status = 0;
   		int istatus =  -1;
   		camera.ackcmd ackdata;
   		long ackHandle = HANDLE_NIL.value;
                int actorIdx = SAL__camera_command_start_ACTOR;

  		// create DataWriter :
  		if (sal[actorIdx].isProcessor == false) {
     			salProcessor(sal[actorIdx].topicName);
     			sal[actorIdx].isProcessor = true;
  		}
  		DataWriter dwriter = getWriter2(SAL__camera_ackcmd_ACTOR);
  		ackcmdDataWriter SALWriter = ackcmdDataWriterHelper.narrow(dwriter);
  		DataReader dreader = getReader(actorIdx);
  		command_startDataReader SALReader = command_startDataReaderHelper.narrow(dreader);
                info = new SampleInfoSeqHolder();
  		istatus = SALReader.take(aCmd, info, 1,ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value, ANY_INSTANCE_STATE.value);
		if (aCmd.value.length > 0) {
   		  if (info.value[0].valid_data) {
    		     if (debugLevel > 8) {
      			System.out.println(  "=== [acceptCommand] start reading a command containing :" );
      			System.out.println(  "    seqNum   : " + aCmd.value[0].private_seqNum );
      			System.out.println(  "    device   : " + aCmd.value[0].device);
      			System.out.println(  "    property : " + aCmd.value[0].property);
      			System.out.println(  "    action   : " + aCmd.value[0].action);
      			System.out.println(  "    value    : " + aCmd.value[0].value);
    		    }
    		    status = aCmd.value[0].private_seqNum;
    		    double rcvdTime = getCurrentTime();
		    double dTime = rcvdTime - aCmd.value[0].private_sndStamp;
    		    if ( dTime < sal[actorIdx].sampleAge ) {
                      ackdata = new camera.ackcmd();
		      ackdata.private_origin = aCmd.value[0].private_origin;
		      ackdata.private_seqNum = aCmd.value[0].private_seqNum;
		      ackdata.error  = 0;
		      ackdata.result = "SAL ACK";
                      data.device    = aCmd.value[0].device;
                      data.property  = aCmd.value[0].property;
                      data.action    = aCmd.value[0].action;
                      data.value     = aCmd.value[0].value;
                      data.configuration = aCmd.value[0].configuration;

		      status = aCmd.value[0].private_seqNum;
		      rcvSeqNum = status;
		      rcvOrigin = aCmd.value[0].private_origin;
		      ackdata.ack = SAL__CMD_ACK;

		      istatus = SALWriter.write(ackdata, ackHandle);
		      SALWriter.unregister_instance(ackdata, ackHandle);
  } else {
    		     if (debugLevel > 8) {
      			System.out.println(  "    Old command ignored :   " + dTime );
                     }
                   }
		 }
                } else {
  	           status = 0;
                }
                SALReader.return_loan(aCmd, info);
	        return status;
	}


	public int waitForCompletion_start( int cmdSeqNum , int timeout )
	{
	   int status = 0;
	   int countdown = timeout*1000;
           int actorIdx = SAL__camera_command_start_ACTOR;
	   ackcmdSeqHolder ackcmd = new ackcmdSeqHolder();

	   while (status != SAL__CMD_COMPLETE && countdown != 0) {
	      status = getResponse_start(ackcmd);
	      if (status != SAL__CMD_NOACK) {
	        if (sal[actorIdx].rcvSeqNum != cmdSeqNum) { 
	           status = SAL__CMD_NOACK;
	        }
	      }
	      try
		{
	 	  Thread.sleep(timeout);
		}
		catch(InterruptedException ie)
		{
			// nothing to do
	      }
	      countdown--;
	   }
	   if (status != SAL__CMD_COMPLETE) {
	      if (debugLevel > 0) {
	         System.out.println( "=== [waitForCompletion_start] command " + cmdSeqNum +  " timed out");
	      } 
	      logError(status);
	   } else {
	      if (debugLevel > 0) {
	         System.out.println( "=== [waitForCompletion_start] command " + cmdSeqNum +  " completed ok");
	      } 
           }
 	   return status;
	}


	public int getResponse_start(ackcmdSeqHolder data)
	{
	  int status =  -1;
          int lastsample = 0;
          int actorIdx = SAL__camera_ackcmd_ACTOR;
          int actorIdxCmd = SAL__camera_command_start_ACTOR;

	  DataReader dreader = getReader2(actorIdx);
	  ackcmdDataReader SALReader = ackcmdDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(data, infoSeq, 1, 
					ANY_SAMPLE_STATE.value,
					ANY_VIEW_STATE.value,
					ANY_INSTANCE_STATE.value);
	  if (data.value.length > 0) {
 		for (int i = 0; i < data.value.length; i++) {
                     if ( debugLevel > 8) {
				System.out.println("=== [getResponse_start] message received :");
				System.out.println("    revCode  : "
						+ data.value[i].private_revCode);
		    }
                    lastsample = i;
		}
	 	status = data.value[lastsample].ack;
	  	sal[actorIdxCmd].rcvSeqNum = data.value[lastsample].private_seqNum;
	  	sal[actorIdxCmd].rcvOrigin = data.value[lastsample].private_origin;
	  } else {
                if ( debugLevel > 8) {
	            System.out.println("=== [getResponse_start] No ack yet!"); 
                }
	        status = SAL__CMD_NOACK;
	  }
    	  SALReader.return_loan(data, infoSeq);
	  return status;
	}


	public int ackCommand_start( int cmdId, int ack, int error, String result )
	{
   		int istatus = -1;
   		long ackHandle = HANDLE_NIL.value;
                int actorIdx = SAL__camera_command_start_ACTOR;
                int actorIdx2 = SAL__camera_ackcmd_ACTOR;

   		camera.ackcmd ackdata;
   		DataWriter dwriter = getWriter2(actorIdx2);
   		ackcmdDataWriter SALWriter = ackcmdDataWriterHelper.narrow(dwriter);
                ackdata = new camera.ackcmd();
   		ackdata.private_origin = sal[actorIdx].rcvOrigin;
   		ackdata.private_seqNum = cmdId;
   		ackdata.error = error;
   		ackdata.ack = ack;
   		ackdata.result = result;

   		if (debugLevel > 0) {
      			System.out.println(  "=== [ackCommand_start] acknowledging a command with :" );
      			System.out.println(  "    seqNum   : " + ackdata.private_seqNum );
      			System.out.println(  "    ack      : " + ackdata.ack );
      			System.out.println(  "    error    : " + ackdata.error );
      			System.out.println(  "    result   : " + ackdata.result );
   		}
   		istatus = SALWriter.write(ackdata, ackHandle);
    		SALWriter.unregister_instance(ackdata, ackHandle);

   		return SAL__OK;
	}


	public int issueCommand_stop( command_stop data )
	{
          Random randGen = new java.util.Random();
  	  long cmdHandle = HANDLE_NIL.value;
          int status;
          int actorIdx = SAL__camera_command_stop_ACTOR;
	  if (sal[actorIdx].isCommand == false) {
	     salCommand(sal[actorIdx].topicName);
	     sal[actorIdx].isCommand = true;
	     sal[actorIdx].sndSeqNum = (int)randGen.nextInt(99999999);
	  }
	  DataWriter dwriter = getWriter(actorIdx);	
	  command_stopDataWriter SALWriter = command_stopDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST COMMAND";
	  data.private_seqNum = sal[actorIdx].sndSeqNum;
          data.private_sndStamp = getCurrentTime();
	  SALWriter.register_instance(data);

	  if (debugLevel > 0) {
	    System.out.println( "=== [issueCommand] stop writing a command containing :");
	    System.out.println( data.device + "." + data.property + "." + data.action + " : " + data.value);
	  }
	  status = SALWriter.write(data, cmdHandle);
	  sal[actorIdx].sndSeqNum++;
	  return (sal[actorIdx].sndSeqNum-1);
	}


	public int acceptCommand_stop( camera.command_stop data )
	{
                command_stopSeqHolder aCmd = new command_stopSeqHolder();
   		SampleInfoSeqHolder info;
   		int status = 0;
   		int istatus =  -1;
   		camera.ackcmd ackdata;
   		long ackHandle = HANDLE_NIL.value;
                int actorIdx = SAL__camera_command_stop_ACTOR;

  		// create DataWriter :
  		if (sal[actorIdx].isProcessor == false) {
     			salProcessor(sal[actorIdx].topicName);
     			sal[actorIdx].isProcessor = true;
  		}
  		DataWriter dwriter = getWriter2(SAL__camera_ackcmd_ACTOR);
  		ackcmdDataWriter SALWriter = ackcmdDataWriterHelper.narrow(dwriter);
  		DataReader dreader = getReader(actorIdx);
  		command_stopDataReader SALReader = command_stopDataReaderHelper.narrow(dreader);
                info = new SampleInfoSeqHolder();
  		istatus = SALReader.take(aCmd, info, 1,ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value, ANY_INSTANCE_STATE.value);
		if (aCmd.value.length > 0) {
   		  if (info.value[0].valid_data) {
    		     if (debugLevel > 8) {
      			System.out.println(  "=== [acceptCommand] stop reading a command containing :" );
      			System.out.println(  "    seqNum   : " + aCmd.value[0].private_seqNum );
      			System.out.println(  "    device   : " + aCmd.value[0].device);
      			System.out.println(  "    property : " + aCmd.value[0].property);
      			System.out.println(  "    action   : " + aCmd.value[0].action);
      			System.out.println(  "    value    : " + aCmd.value[0].value);
    		    }
    		    status = aCmd.value[0].private_seqNum;
    		    double rcvdTime = getCurrentTime();
		    double dTime = rcvdTime - aCmd.value[0].private_sndStamp;
    		    if ( dTime < sal[actorIdx].sampleAge ) {
                      ackdata = new camera.ackcmd();
		      ackdata.private_origin = aCmd.value[0].private_origin;
		      ackdata.private_seqNum = aCmd.value[0].private_seqNum;
		      ackdata.error  = 0;
		      ackdata.result = "SAL ACK";
                      data.device    = aCmd.value[0].device;
                      data.property  = aCmd.value[0].property;
                      data.action    = aCmd.value[0].action;
                      data.value     = aCmd.value[0].value;
                      data.state = aCmd.value[0].state;

		      status = aCmd.value[0].private_seqNum;
		      rcvSeqNum = status;
		      rcvOrigin = aCmd.value[0].private_origin;
		      ackdata.ack = SAL__CMD_ACK;

		      istatus = SALWriter.write(ackdata, ackHandle);
		      SALWriter.unregister_instance(ackdata, ackHandle);
  } else {
    		     if (debugLevel > 8) {
      			System.out.println(  "    Old command ignored :   " + dTime );
                     }
                   }
		 }
                } else {
  	           status = 0;
                }
                SALReader.return_loan(aCmd, info);
	        return status;
	}


	public int waitForCompletion_stop( int cmdSeqNum , int timeout )
	{
	   int status = 0;
	   int countdown = timeout*1000;
           int actorIdx = SAL__camera_command_stop_ACTOR;
	   ackcmdSeqHolder ackcmd = new ackcmdSeqHolder();

	   while (status != SAL__CMD_COMPLETE && countdown != 0) {
	      status = getResponse_stop(ackcmd);
	      if (status != SAL__CMD_NOACK) {
	        if (sal[actorIdx].rcvSeqNum != cmdSeqNum) { 
	           status = SAL__CMD_NOACK;
	        }
	      }
	      try
		{
	 	  Thread.sleep(timeout);
		}
		catch(InterruptedException ie)
		{
			// nothing to do
	      }
	      countdown--;
	   }
	   if (status != SAL__CMD_COMPLETE) {
	      if (debugLevel > 0) {
	         System.out.println( "=== [waitForCompletion_stop] command " + cmdSeqNum +  " timed out");
	      } 
	      logError(status);
	   } else {
	      if (debugLevel > 0) {
	         System.out.println( "=== [waitForCompletion_stop] command " + cmdSeqNum +  " completed ok");
	      } 
           }
 	   return status;
	}


	public int getResponse_stop(ackcmdSeqHolder data)
	{
	  int status =  -1;
          int lastsample = 0;
          int actorIdx = SAL__camera_ackcmd_ACTOR;
          int actorIdxCmd = SAL__camera_command_stop_ACTOR;

	  DataReader dreader = getReader2(actorIdx);
	  ackcmdDataReader SALReader = ackcmdDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(data, infoSeq, 1, 
					ANY_SAMPLE_STATE.value,
					ANY_VIEW_STATE.value,
					ANY_INSTANCE_STATE.value);
	  if (data.value.length > 0) {
 		for (int i = 0; i < data.value.length; i++) {
                     if ( debugLevel > 8) {
				System.out.println("=== [getResponse_stop] message received :");
				System.out.println("    revCode  : "
						+ data.value[i].private_revCode);
		    }
                    lastsample = i;
		}
	 	status = data.value[lastsample].ack;
	  	sal[actorIdxCmd].rcvSeqNum = data.value[lastsample].private_seqNum;
	  	sal[actorIdxCmd].rcvOrigin = data.value[lastsample].private_origin;
	  } else {
                if ( debugLevel > 8) {
	            System.out.println("=== [getResponse_stop] No ack yet!"); 
                }
	        status = SAL__CMD_NOACK;
	  }
    	  SALReader.return_loan(data, infoSeq);
	  return status;
	}


	public int ackCommand_stop( int cmdId, int ack, int error, String result )
	{
   		int istatus = -1;
   		long ackHandle = HANDLE_NIL.value;
                int actorIdx = SAL__camera_command_stop_ACTOR;
                int actorIdx2 = SAL__camera_ackcmd_ACTOR;

   		camera.ackcmd ackdata;
   		DataWriter dwriter = getWriter2(actorIdx2);
   		ackcmdDataWriter SALWriter = ackcmdDataWriterHelper.narrow(dwriter);
                ackdata = new camera.ackcmd();
   		ackdata.private_origin = sal[actorIdx].rcvOrigin;
   		ackdata.private_seqNum = cmdId;
   		ackdata.error = error;
   		ackdata.ack = ack;
   		ackdata.result = result;

   		if (debugLevel > 0) {
      			System.out.println(  "=== [ackCommand_stop] acknowledging a command with :" );
      			System.out.println(  "    seqNum   : " + ackdata.private_seqNum );
      			System.out.println(  "    ack      : " + ackdata.ack );
      			System.out.println(  "    error    : " + ackdata.error );
      			System.out.println(  "    result   : " + ackdata.result );
   		}
   		istatus = SALWriter.write(ackdata, ackHandle);
    		SALWriter.unregister_instance(ackdata, ackHandle);

   		return SAL__OK;
	}


	public int issueCommand_abort( command_abort data )
	{
          Random randGen = new java.util.Random();
  	  long cmdHandle = HANDLE_NIL.value;
          int status;
          int actorIdx = SAL__camera_command_abort_ACTOR;
	  if (sal[actorIdx].isCommand == false) {
	     salCommand(sal[actorIdx].topicName);
	     sal[actorIdx].isCommand = true;
	     sal[actorIdx].sndSeqNum = (int)randGen.nextInt(99999999);
	  }
	  DataWriter dwriter = getWriter(actorIdx);	
	  command_abortDataWriter SALWriter = command_abortDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST COMMAND";
	  data.private_seqNum = sal[actorIdx].sndSeqNum;
          data.private_sndStamp = getCurrentTime();
	  SALWriter.register_instance(data);

	  if (debugLevel > 0) {
	    System.out.println( "=== [issueCommand] abort writing a command containing :");
	    System.out.println( data.device + "." + data.property + "." + data.action + " : " + data.value);
	  }
	  status = SALWriter.write(data, cmdHandle);
	  sal[actorIdx].sndSeqNum++;
	  return (sal[actorIdx].sndSeqNum-1);
	}


	public int acceptCommand_abort( camera.command_abort data )
	{
                command_abortSeqHolder aCmd = new command_abortSeqHolder();
   		SampleInfoSeqHolder info;
   		int status = 0;
   		int istatus =  -1;
   		camera.ackcmd ackdata;
   		long ackHandle = HANDLE_NIL.value;
                int actorIdx = SAL__camera_command_abort_ACTOR;

  		// create DataWriter :
  		if (sal[actorIdx].isProcessor == false) {
     			salProcessor(sal[actorIdx].topicName);
     			sal[actorIdx].isProcessor = true;
  		}
  		DataWriter dwriter = getWriter2(SAL__camera_ackcmd_ACTOR);
  		ackcmdDataWriter SALWriter = ackcmdDataWriterHelper.narrow(dwriter);
  		DataReader dreader = getReader(actorIdx);
  		command_abortDataReader SALReader = command_abortDataReaderHelper.narrow(dreader);
                info = new SampleInfoSeqHolder();
  		istatus = SALReader.take(aCmd, info, 1,ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value, ANY_INSTANCE_STATE.value);
		if (aCmd.value.length > 0) {
   		  if (info.value[0].valid_data) {
    		     if (debugLevel > 8) {
      			System.out.println(  "=== [acceptCommand] abort reading a command containing :" );
      			System.out.println(  "    seqNum   : " + aCmd.value[0].private_seqNum );
      			System.out.println(  "    device   : " + aCmd.value[0].device);
      			System.out.println(  "    property : " + aCmd.value[0].property);
      			System.out.println(  "    action   : " + aCmd.value[0].action);
      			System.out.println(  "    value    : " + aCmd.value[0].value);
    		    }
    		    status = aCmd.value[0].private_seqNum;
    		    double rcvdTime = getCurrentTime();
		    double dTime = rcvdTime - aCmd.value[0].private_sndStamp;
    		    if ( dTime < sal[actorIdx].sampleAge ) {
                      ackdata = new camera.ackcmd();
		      ackdata.private_origin = aCmd.value[0].private_origin;
		      ackdata.private_seqNum = aCmd.value[0].private_seqNum;
		      ackdata.error  = 0;
		      ackdata.result = "SAL ACK";
                      data.device    = aCmd.value[0].device;
                      data.property  = aCmd.value[0].property;
                      data.action    = aCmd.value[0].action;
                      data.value     = aCmd.value[0].value;
                      data.state = aCmd.value[0].state;

		      status = aCmd.value[0].private_seqNum;
		      rcvSeqNum = status;
		      rcvOrigin = aCmd.value[0].private_origin;
		      ackdata.ack = SAL__CMD_ACK;

		      istatus = SALWriter.write(ackdata, ackHandle);
		      SALWriter.unregister_instance(ackdata, ackHandle);
  } else {
    		     if (debugLevel > 8) {
      			System.out.println(  "    Old command ignored :   " + dTime );
                     }
                   }
		 }
                } else {
  	           status = 0;
                }
                SALReader.return_loan(aCmd, info);
	        return status;
	}


	public int waitForCompletion_abort( int cmdSeqNum , int timeout )
	{
	   int status = 0;
	   int countdown = timeout*1000;
           int actorIdx = SAL__camera_command_abort_ACTOR;
	   ackcmdSeqHolder ackcmd = new ackcmdSeqHolder();

	   while (status != SAL__CMD_COMPLETE && countdown != 0) {
	      status = getResponse_abort(ackcmd);
	      if (status != SAL__CMD_NOACK) {
	        if (sal[actorIdx].rcvSeqNum != cmdSeqNum) { 
	           status = SAL__CMD_NOACK;
	        }
	      }
	      try
		{
	 	  Thread.sleep(timeout);
		}
		catch(InterruptedException ie)
		{
			// nothing to do
	      }
	      countdown--;
	   }
	   if (status != SAL__CMD_COMPLETE) {
	      if (debugLevel > 0) {
	         System.out.println( "=== [waitForCompletion_abort] command " + cmdSeqNum +  " timed out");
	      } 
	      logError(status);
	   } else {
	      if (debugLevel > 0) {
	         System.out.println( "=== [waitForCompletion_abort] command " + cmdSeqNum +  " completed ok");
	      } 
           }
 	   return status;
	}


	public int getResponse_abort(ackcmdSeqHolder data)
	{
	  int status =  -1;
          int lastsample = 0;
          int actorIdx = SAL__camera_ackcmd_ACTOR;
          int actorIdxCmd = SAL__camera_command_abort_ACTOR;

	  DataReader dreader = getReader2(actorIdx);
	  ackcmdDataReader SALReader = ackcmdDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(data, infoSeq, 1, 
					ANY_SAMPLE_STATE.value,
					ANY_VIEW_STATE.value,
					ANY_INSTANCE_STATE.value);
	  if (data.value.length > 0) {
 		for (int i = 0; i < data.value.length; i++) {
                     if ( debugLevel > 8) {
				System.out.println("=== [getResponse_abort] message received :");
				System.out.println("    revCode  : "
						+ data.value[i].private_revCode);
		    }
                    lastsample = i;
		}
	 	status = data.value[lastsample].ack;
	  	sal[actorIdxCmd].rcvSeqNum = data.value[lastsample].private_seqNum;
	  	sal[actorIdxCmd].rcvOrigin = data.value[lastsample].private_origin;
	  } else {
                if ( debugLevel > 8) {
	            System.out.println("=== [getResponse_abort] No ack yet!"); 
                }
	        status = SAL__CMD_NOACK;
	  }
    	  SALReader.return_loan(data, infoSeq);
	  return status;
	}


	public int ackCommand_abort( int cmdId, int ack, int error, String result )
	{
   		int istatus = -1;
   		long ackHandle = HANDLE_NIL.value;
                int actorIdx = SAL__camera_command_abort_ACTOR;
                int actorIdx2 = SAL__camera_ackcmd_ACTOR;

   		camera.ackcmd ackdata;
   		DataWriter dwriter = getWriter2(actorIdx2);
   		ackcmdDataWriter SALWriter = ackcmdDataWriterHelper.narrow(dwriter);
                ackdata = new camera.ackcmd();
   		ackdata.private_origin = sal[actorIdx].rcvOrigin;
   		ackdata.private_seqNum = cmdId;
   		ackdata.error = error;
   		ackdata.ack = ack;
   		ackdata.result = result;

   		if (debugLevel > 0) {
      			System.out.println(  "=== [ackCommand_abort] acknowledging a command with :" );
      			System.out.println(  "    seqNum   : " + ackdata.private_seqNum );
      			System.out.println(  "    ack      : " + ackdata.ack );
      			System.out.println(  "    error    : " + ackdata.error );
      			System.out.println(  "    result   : " + ackdata.result );
   		}
   		istatus = SALWriter.write(ackdata, ackHandle);
    		SALWriter.unregister_instance(ackdata, ackHandle);

   		return SAL__OK;
	}


	public int issueCommand_enable( command_enable data )
	{
          Random randGen = new java.util.Random();
  	  long cmdHandle = HANDLE_NIL.value;
          int status;
          int actorIdx = SAL__camera_command_enable_ACTOR;
	  if (sal[actorIdx].isCommand == false) {
	     salCommand(sal[actorIdx].topicName);
	     sal[actorIdx].isCommand = true;
	     sal[actorIdx].sndSeqNum = (int)randGen.nextInt(99999999);
	  }
	  DataWriter dwriter = getWriter(actorIdx);	
	  command_enableDataWriter SALWriter = command_enableDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST COMMAND";
	  data.private_seqNum = sal[actorIdx].sndSeqNum;
          data.private_sndStamp = getCurrentTime();
	  SALWriter.register_instance(data);

	  if (debugLevel > 0) {
	    System.out.println( "=== [issueCommand] enable writing a command containing :");
	    System.out.println( data.device + "." + data.property + "." + data.action + " : " + data.value);
	  }
	  status = SALWriter.write(data, cmdHandle);
	  sal[actorIdx].sndSeqNum++;
	  return (sal[actorIdx].sndSeqNum-1);
	}


	public int acceptCommand_enable( camera.command_enable data )
	{
                command_enableSeqHolder aCmd = new command_enableSeqHolder();
   		SampleInfoSeqHolder info;
   		int status = 0;
   		int istatus =  -1;
   		camera.ackcmd ackdata;
   		long ackHandle = HANDLE_NIL.value;
                int actorIdx = SAL__camera_command_enable_ACTOR;

  		// create DataWriter :
  		if (sal[actorIdx].isProcessor == false) {
     			salProcessor(sal[actorIdx].topicName);
     			sal[actorIdx].isProcessor = true;
  		}
  		DataWriter dwriter = getWriter2(SAL__camera_ackcmd_ACTOR);
  		ackcmdDataWriter SALWriter = ackcmdDataWriterHelper.narrow(dwriter);
  		DataReader dreader = getReader(actorIdx);
  		command_enableDataReader SALReader = command_enableDataReaderHelper.narrow(dreader);
                info = new SampleInfoSeqHolder();
  		istatus = SALReader.take(aCmd, info, 1,ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value, ANY_INSTANCE_STATE.value);
		if (aCmd.value.length > 0) {
   		  if (info.value[0].valid_data) {
    		     if (debugLevel > 8) {
      			System.out.println(  "=== [acceptCommand] enable reading a command containing :" );
      			System.out.println(  "    seqNum   : " + aCmd.value[0].private_seqNum );
      			System.out.println(  "    device   : " + aCmd.value[0].device);
      			System.out.println(  "    property : " + aCmd.value[0].property);
      			System.out.println(  "    action   : " + aCmd.value[0].action);
      			System.out.println(  "    value    : " + aCmd.value[0].value);
    		    }
    		    status = aCmd.value[0].private_seqNum;
    		    double rcvdTime = getCurrentTime();
		    double dTime = rcvdTime - aCmd.value[0].private_sndStamp;
    		    if ( dTime < sal[actorIdx].sampleAge ) {
                      ackdata = new camera.ackcmd();
		      ackdata.private_origin = aCmd.value[0].private_origin;
		      ackdata.private_seqNum = aCmd.value[0].private_seqNum;
		      ackdata.error  = 0;
		      ackdata.result = "SAL ACK";
                      data.device    = aCmd.value[0].device;
                      data.property  = aCmd.value[0].property;
                      data.action    = aCmd.value[0].action;
                      data.value     = aCmd.value[0].value;
                      data.state = aCmd.value[0].state;

		      status = aCmd.value[0].private_seqNum;
		      rcvSeqNum = status;
		      rcvOrigin = aCmd.value[0].private_origin;
		      ackdata.ack = SAL__CMD_ACK;

		      istatus = SALWriter.write(ackdata, ackHandle);
		      SALWriter.unregister_instance(ackdata, ackHandle);
  } else {
    		     if (debugLevel > 8) {
      			System.out.println(  "    Old command ignored :   " + dTime );
                     }
                   }
		 }
                } else {
  	           status = 0;
                }
                SALReader.return_loan(aCmd, info);
	        return status;
	}


	public int waitForCompletion_enable( int cmdSeqNum , int timeout )
	{
	   int status = 0;
	   int countdown = timeout*1000;
           int actorIdx = SAL__camera_command_enable_ACTOR;
	   ackcmdSeqHolder ackcmd = new ackcmdSeqHolder();

	   while (status != SAL__CMD_COMPLETE && countdown != 0) {
	      status = getResponse_enable(ackcmd);
	      if (status != SAL__CMD_NOACK) {
	        if (sal[actorIdx].rcvSeqNum != cmdSeqNum) { 
	           status = SAL__CMD_NOACK;
	        }
	      }
	      try
		{
	 	  Thread.sleep(timeout);
		}
		catch(InterruptedException ie)
		{
			// nothing to do
	      }
	      countdown--;
	   }
	   if (status != SAL__CMD_COMPLETE) {
	      if (debugLevel > 0) {
	         System.out.println( "=== [waitForCompletion_enable] command " + cmdSeqNum +  " timed out");
	      } 
	      logError(status);
	   } else {
	      if (debugLevel > 0) {
	         System.out.println( "=== [waitForCompletion_enable] command " + cmdSeqNum +  " completed ok");
	      } 
           }
 	   return status;
	}


	public int getResponse_enable(ackcmdSeqHolder data)
	{
	  int status =  -1;
          int lastsample = 0;
          int actorIdx = SAL__camera_ackcmd_ACTOR;
          int actorIdxCmd = SAL__camera_command_enable_ACTOR;

	  DataReader dreader = getReader2(actorIdx);
	  ackcmdDataReader SALReader = ackcmdDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(data, infoSeq, 1, 
					ANY_SAMPLE_STATE.value,
					ANY_VIEW_STATE.value,
					ANY_INSTANCE_STATE.value);
	  if (data.value.length > 0) {
 		for (int i = 0; i < data.value.length; i++) {
                     if ( debugLevel > 8) {
				System.out.println("=== [getResponse_enable] message received :");
				System.out.println("    revCode  : "
						+ data.value[i].private_revCode);
		    }
                    lastsample = i;
		}
	 	status = data.value[lastsample].ack;
	  	sal[actorIdxCmd].rcvSeqNum = data.value[lastsample].private_seqNum;
	  	sal[actorIdxCmd].rcvOrigin = data.value[lastsample].private_origin;
	  } else {
                if ( debugLevel > 8) {
	            System.out.println("=== [getResponse_enable] No ack yet!"); 
                }
	        status = SAL__CMD_NOACK;
	  }
    	  SALReader.return_loan(data, infoSeq);
	  return status;
	}


	public int ackCommand_enable( int cmdId, int ack, int error, String result )
	{
   		int istatus = -1;
   		long ackHandle = HANDLE_NIL.value;
                int actorIdx = SAL__camera_command_enable_ACTOR;
                int actorIdx2 = SAL__camera_ackcmd_ACTOR;

   		camera.ackcmd ackdata;
   		DataWriter dwriter = getWriter2(actorIdx2);
   		ackcmdDataWriter SALWriter = ackcmdDataWriterHelper.narrow(dwriter);
                ackdata = new camera.ackcmd();
   		ackdata.private_origin = sal[actorIdx].rcvOrigin;
   		ackdata.private_seqNum = cmdId;
   		ackdata.error = error;
   		ackdata.ack = ack;
   		ackdata.result = result;

   		if (debugLevel > 0) {
      			System.out.println(  "=== [ackCommand_enable] acknowledging a command with :" );
      			System.out.println(  "    seqNum   : " + ackdata.private_seqNum );
      			System.out.println(  "    ack      : " + ackdata.ack );
      			System.out.println(  "    error    : " + ackdata.error );
      			System.out.println(  "    result   : " + ackdata.result );
   		}
   		istatus = SALWriter.write(ackdata, ackHandle);
    		SALWriter.unregister_instance(ackdata, ackHandle);

   		return SAL__OK;
	}


	public int issueCommand_disable( command_disable data )
	{
          Random randGen = new java.util.Random();
  	  long cmdHandle = HANDLE_NIL.value;
          int status;
          int actorIdx = SAL__camera_command_disable_ACTOR;
	  if (sal[actorIdx].isCommand == false) {
	     salCommand(sal[actorIdx].topicName);
	     sal[actorIdx].isCommand = true;
	     sal[actorIdx].sndSeqNum = (int)randGen.nextInt(99999999);
	  }
	  DataWriter dwriter = getWriter(actorIdx);	
	  command_disableDataWriter SALWriter = command_disableDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST COMMAND";
	  data.private_seqNum = sal[actorIdx].sndSeqNum;
          data.private_sndStamp = getCurrentTime();
	  SALWriter.register_instance(data);

	  if (debugLevel > 0) {
	    System.out.println( "=== [issueCommand] disable writing a command containing :");
	    System.out.println( data.device + "." + data.property + "." + data.action + " : " + data.value);
	  }
	  status = SALWriter.write(data, cmdHandle);
	  sal[actorIdx].sndSeqNum++;
	  return (sal[actorIdx].sndSeqNum-1);
	}


	public int acceptCommand_disable( camera.command_disable data )
	{
                command_disableSeqHolder aCmd = new command_disableSeqHolder();
   		SampleInfoSeqHolder info;
   		int status = 0;
   		int istatus =  -1;
   		camera.ackcmd ackdata;
   		long ackHandle = HANDLE_NIL.value;
                int actorIdx = SAL__camera_command_disable_ACTOR;

  		// create DataWriter :
  		if (sal[actorIdx].isProcessor == false) {
     			salProcessor(sal[actorIdx].topicName);
     			sal[actorIdx].isProcessor = true;
  		}
  		DataWriter dwriter = getWriter2(SAL__camera_ackcmd_ACTOR);
  		ackcmdDataWriter SALWriter = ackcmdDataWriterHelper.narrow(dwriter);
  		DataReader dreader = getReader(actorIdx);
  		command_disableDataReader SALReader = command_disableDataReaderHelper.narrow(dreader);
                info = new SampleInfoSeqHolder();
  		istatus = SALReader.take(aCmd, info, 1,ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value, ANY_INSTANCE_STATE.value);
		if (aCmd.value.length > 0) {
   		  if (info.value[0].valid_data) {
    		     if (debugLevel > 8) {
      			System.out.println(  "=== [acceptCommand] disable reading a command containing :" );
      			System.out.println(  "    seqNum   : " + aCmd.value[0].private_seqNum );
      			System.out.println(  "    device   : " + aCmd.value[0].device);
      			System.out.println(  "    property : " + aCmd.value[0].property);
      			System.out.println(  "    action   : " + aCmd.value[0].action);
      			System.out.println(  "    value    : " + aCmd.value[0].value);
    		    }
    		    status = aCmd.value[0].private_seqNum;
    		    double rcvdTime = getCurrentTime();
		    double dTime = rcvdTime - aCmd.value[0].private_sndStamp;
    		    if ( dTime < sal[actorIdx].sampleAge ) {
                      ackdata = new camera.ackcmd();
		      ackdata.private_origin = aCmd.value[0].private_origin;
		      ackdata.private_seqNum = aCmd.value[0].private_seqNum;
		      ackdata.error  = 0;
		      ackdata.result = "SAL ACK";
                      data.device    = aCmd.value[0].device;
                      data.property  = aCmd.value[0].property;
                      data.action    = aCmd.value[0].action;
                      data.value     = aCmd.value[0].value;
                      data.state = aCmd.value[0].state;

		      status = aCmd.value[0].private_seqNum;
		      rcvSeqNum = status;
		      rcvOrigin = aCmd.value[0].private_origin;
		      ackdata.ack = SAL__CMD_ACK;

		      istatus = SALWriter.write(ackdata, ackHandle);
		      SALWriter.unregister_instance(ackdata, ackHandle);
  } else {
    		     if (debugLevel > 8) {
      			System.out.println(  "    Old command ignored :   " + dTime );
                     }
                   }
		 }
                } else {
  	           status = 0;
                }
                SALReader.return_loan(aCmd, info);
	        return status;
	}


	public int waitForCompletion_disable( int cmdSeqNum , int timeout )
	{
	   int status = 0;
	   int countdown = timeout*1000;
           int actorIdx = SAL__camera_command_disable_ACTOR;
	   ackcmdSeqHolder ackcmd = new ackcmdSeqHolder();

	   while (status != SAL__CMD_COMPLETE && countdown != 0) {
	      status = getResponse_disable(ackcmd);
	      if (status != SAL__CMD_NOACK) {
	        if (sal[actorIdx].rcvSeqNum != cmdSeqNum) { 
	           status = SAL__CMD_NOACK;
	        }
	      }
	      try
		{
	 	  Thread.sleep(timeout);
		}
		catch(InterruptedException ie)
		{
			// nothing to do
	      }
	      countdown--;
	   }
	   if (status != SAL__CMD_COMPLETE) {
	      if (debugLevel > 0) {
	         System.out.println( "=== [waitForCompletion_disable] command " + cmdSeqNum +  " timed out");
	      } 
	      logError(status);
	   } else {
	      if (debugLevel > 0) {
	         System.out.println( "=== [waitForCompletion_disable] command " + cmdSeqNum +  " completed ok");
	      } 
           }
 	   return status;
	}


	public int getResponse_disable(ackcmdSeqHolder data)
	{
	  int status =  -1;
          int lastsample = 0;
          int actorIdx = SAL__camera_ackcmd_ACTOR;
          int actorIdxCmd = SAL__camera_command_disable_ACTOR;

	  DataReader dreader = getReader2(actorIdx);
	  ackcmdDataReader SALReader = ackcmdDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(data, infoSeq, 1, 
					ANY_SAMPLE_STATE.value,
					ANY_VIEW_STATE.value,
					ANY_INSTANCE_STATE.value);
	  if (data.value.length > 0) {
 		for (int i = 0; i < data.value.length; i++) {
                     if ( debugLevel > 8) {
				System.out.println("=== [getResponse_disable] message received :");
				System.out.println("    revCode  : "
						+ data.value[i].private_revCode);
		    }
                    lastsample = i;
		}
	 	status = data.value[lastsample].ack;
	  	sal[actorIdxCmd].rcvSeqNum = data.value[lastsample].private_seqNum;
	  	sal[actorIdxCmd].rcvOrigin = data.value[lastsample].private_origin;
	  } else {
                if ( debugLevel > 8) {
	            System.out.println("=== [getResponse_disable] No ack yet!"); 
                }
	        status = SAL__CMD_NOACK;
	  }
    	  SALReader.return_loan(data, infoSeq);
	  return status;
	}


	public int ackCommand_disable( int cmdId, int ack, int error, String result )
	{
   		int istatus = -1;
   		long ackHandle = HANDLE_NIL.value;
                int actorIdx = SAL__camera_command_disable_ACTOR;
                int actorIdx2 = SAL__camera_ackcmd_ACTOR;

   		camera.ackcmd ackdata;
   		DataWriter dwriter = getWriter2(actorIdx2);
   		ackcmdDataWriter SALWriter = ackcmdDataWriterHelper.narrow(dwriter);
                ackdata = new camera.ackcmd();
   		ackdata.private_origin = sal[actorIdx].rcvOrigin;
   		ackdata.private_seqNum = cmdId;
   		ackdata.error = error;
   		ackdata.ack = ack;
   		ackdata.result = result;

   		if (debugLevel > 0) {
      			System.out.println(  "=== [ackCommand_disable] acknowledging a command with :" );
      			System.out.println(  "    seqNum   : " + ackdata.private_seqNum );
      			System.out.println(  "    ack      : " + ackdata.ack );
      			System.out.println(  "    error    : " + ackdata.error );
      			System.out.println(  "    result   : " + ackdata.result );
   		}
   		istatus = SALWriter.write(ackdata, ackHandle);
    		SALWriter.unregister_instance(ackdata, ackHandle);

   		return SAL__OK;
	}


	public int issueCommand_standby( command_standby data )
	{
          Random randGen = new java.util.Random();
  	  long cmdHandle = HANDLE_NIL.value;
          int status;
          int actorIdx = SAL__camera_command_standby_ACTOR;
	  if (sal[actorIdx].isCommand == false) {
	     salCommand(sal[actorIdx].topicName);
	     sal[actorIdx].isCommand = true;
	     sal[actorIdx].sndSeqNum = (int)randGen.nextInt(99999999);
	  }
	  DataWriter dwriter = getWriter(actorIdx);	
	  command_standbyDataWriter SALWriter = command_standbyDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST COMMAND";
	  data.private_seqNum = sal[actorIdx].sndSeqNum;
          data.private_sndStamp = getCurrentTime();
	  SALWriter.register_instance(data);

	  if (debugLevel > 0) {
	    System.out.println( "=== [issueCommand] standby writing a command containing :");
	    System.out.println( data.device + "." + data.property + "." + data.action + " : " + data.value);
	  }
	  status = SALWriter.write(data, cmdHandle);
	  sal[actorIdx].sndSeqNum++;
	  return (sal[actorIdx].sndSeqNum-1);
	}


	public int acceptCommand_standby( camera.command_standby data )
	{
                command_standbySeqHolder aCmd = new command_standbySeqHolder();
   		SampleInfoSeqHolder info;
   		int status = 0;
   		int istatus =  -1;
   		camera.ackcmd ackdata;
   		long ackHandle = HANDLE_NIL.value;
                int actorIdx = SAL__camera_command_standby_ACTOR;

  		// create DataWriter :
  		if (sal[actorIdx].isProcessor == false) {
     			salProcessor(sal[actorIdx].topicName);
     			sal[actorIdx].isProcessor = true;
  		}
  		DataWriter dwriter = getWriter2(SAL__camera_ackcmd_ACTOR);
  		ackcmdDataWriter SALWriter = ackcmdDataWriterHelper.narrow(dwriter);
  		DataReader dreader = getReader(actorIdx);
  		command_standbyDataReader SALReader = command_standbyDataReaderHelper.narrow(dreader);
                info = new SampleInfoSeqHolder();
  		istatus = SALReader.take(aCmd, info, 1,ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value, ANY_INSTANCE_STATE.value);
		if (aCmd.value.length > 0) {
   		  if (info.value[0].valid_data) {
    		     if (debugLevel > 8) {
      			System.out.println(  "=== [acceptCommand] standby reading a command containing :" );
      			System.out.println(  "    seqNum   : " + aCmd.value[0].private_seqNum );
      			System.out.println(  "    device   : " + aCmd.value[0].device);
      			System.out.println(  "    property : " + aCmd.value[0].property);
      			System.out.println(  "    action   : " + aCmd.value[0].action);
      			System.out.println(  "    value    : " + aCmd.value[0].value);
    		    }
    		    status = aCmd.value[0].private_seqNum;
    		    double rcvdTime = getCurrentTime();
		    double dTime = rcvdTime - aCmd.value[0].private_sndStamp;
    		    if ( dTime < sal[actorIdx].sampleAge ) {
                      ackdata = new camera.ackcmd();
		      ackdata.private_origin = aCmd.value[0].private_origin;
		      ackdata.private_seqNum = aCmd.value[0].private_seqNum;
		      ackdata.error  = 0;
		      ackdata.result = "SAL ACK";
                      data.device    = aCmd.value[0].device;
                      data.property  = aCmd.value[0].property;
                      data.action    = aCmd.value[0].action;
                      data.value     = aCmd.value[0].value;
                      data.state = aCmd.value[0].state;

		      status = aCmd.value[0].private_seqNum;
		      rcvSeqNum = status;
		      rcvOrigin = aCmd.value[0].private_origin;
		      ackdata.ack = SAL__CMD_ACK;

		      istatus = SALWriter.write(ackdata, ackHandle);
		      SALWriter.unregister_instance(ackdata, ackHandle);
  } else {
    		     if (debugLevel > 8) {
      			System.out.println(  "    Old command ignored :   " + dTime );
                     }
                   }
		 }
                } else {
  	           status = 0;
                }
                SALReader.return_loan(aCmd, info);
	        return status;
	}


	public int waitForCompletion_standby( int cmdSeqNum , int timeout )
	{
	   int status = 0;
	   int countdown = timeout*1000;
           int actorIdx = SAL__camera_command_standby_ACTOR;
	   ackcmdSeqHolder ackcmd = new ackcmdSeqHolder();

	   while (status != SAL__CMD_COMPLETE && countdown != 0) {
	      status = getResponse_standby(ackcmd);
	      if (status != SAL__CMD_NOACK) {
	        if (sal[actorIdx].rcvSeqNum != cmdSeqNum) { 
	           status = SAL__CMD_NOACK;
	        }
	      }
	      try
		{
	 	  Thread.sleep(timeout);
		}
		catch(InterruptedException ie)
		{
			// nothing to do
	      }
	      countdown--;
	   }
	   if (status != SAL__CMD_COMPLETE) {
	      if (debugLevel > 0) {
	         System.out.println( "=== [waitForCompletion_standby] command " + cmdSeqNum +  " timed out");
	      } 
	      logError(status);
	   } else {
	      if (debugLevel > 0) {
	         System.out.println( "=== [waitForCompletion_standby] command " + cmdSeqNum +  " completed ok");
	      } 
           }
 	   return status;
	}


	public int getResponse_standby(ackcmdSeqHolder data)
	{
	  int status =  -1;
          int lastsample = 0;
          int actorIdx = SAL__camera_ackcmd_ACTOR;
          int actorIdxCmd = SAL__camera_command_standby_ACTOR;

	  DataReader dreader = getReader2(actorIdx);
	  ackcmdDataReader SALReader = ackcmdDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(data, infoSeq, 1, 
					ANY_SAMPLE_STATE.value,
					ANY_VIEW_STATE.value,
					ANY_INSTANCE_STATE.value);
	  if (data.value.length > 0) {
 		for (int i = 0; i < data.value.length; i++) {
                     if ( debugLevel > 8) {
				System.out.println("=== [getResponse_standby] message received :");
				System.out.println("    revCode  : "
						+ data.value[i].private_revCode);
		    }
                    lastsample = i;
		}
	 	status = data.value[lastsample].ack;
	  	sal[actorIdxCmd].rcvSeqNum = data.value[lastsample].private_seqNum;
	  	sal[actorIdxCmd].rcvOrigin = data.value[lastsample].private_origin;
	  } else {
                if ( debugLevel > 8) {
	            System.out.println("=== [getResponse_standby] No ack yet!"); 
                }
	        status = SAL__CMD_NOACK;
	  }
    	  SALReader.return_loan(data, infoSeq);
	  return status;
	}


	public int ackCommand_standby( int cmdId, int ack, int error, String result )
	{
   		int istatus = -1;
   		long ackHandle = HANDLE_NIL.value;
                int actorIdx = SAL__camera_command_standby_ACTOR;
                int actorIdx2 = SAL__camera_ackcmd_ACTOR;

   		camera.ackcmd ackdata;
   		DataWriter dwriter = getWriter2(actorIdx2);
   		ackcmdDataWriter SALWriter = ackcmdDataWriterHelper.narrow(dwriter);
                ackdata = new camera.ackcmd();
   		ackdata.private_origin = sal[actorIdx].rcvOrigin;
   		ackdata.private_seqNum = cmdId;
   		ackdata.error = error;
   		ackdata.ack = ack;
   		ackdata.result = result;

   		if (debugLevel > 0) {
      			System.out.println(  "=== [ackCommand_standby] acknowledging a command with :" );
      			System.out.println(  "    seqNum   : " + ackdata.private_seqNum );
      			System.out.println(  "    ack      : " + ackdata.ack );
      			System.out.println(  "    error    : " + ackdata.error );
      			System.out.println(  "    result   : " + ackdata.result );
   		}
   		istatus = SALWriter.write(ackdata, ackHandle);
    		SALWriter.unregister_instance(ackdata, ackHandle);

   		return SAL__OK;
	}


	public int issueCommand_exitControl( command_exitControl data )
	{
          Random randGen = new java.util.Random();
  	  long cmdHandle = HANDLE_NIL.value;
          int status;
          int actorIdx = SAL__camera_command_exitControl_ACTOR;
	  if (sal[actorIdx].isCommand == false) {
	     salCommand(sal[actorIdx].topicName);
	     sal[actorIdx].isCommand = true;
	     sal[actorIdx].sndSeqNum = (int)randGen.nextInt(99999999);
	  }
	  DataWriter dwriter = getWriter(actorIdx);	
	  command_exitControlDataWriter SALWriter = command_exitControlDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST COMMAND";
	  data.private_seqNum = sal[actorIdx].sndSeqNum;
          data.private_sndStamp = getCurrentTime();
	  SALWriter.register_instance(data);

	  if (debugLevel > 0) {
	    System.out.println( "=== [issueCommand] exitControl writing a command containing :");
	    System.out.println( data.device + "." + data.property + "." + data.action + " : " + data.value);
	  }
	  status = SALWriter.write(data, cmdHandle);
	  sal[actorIdx].sndSeqNum++;
	  return (sal[actorIdx].sndSeqNum-1);
	}


	public int acceptCommand_exitControl( camera.command_exitControl data )
	{
                command_exitControlSeqHolder aCmd = new command_exitControlSeqHolder();
   		SampleInfoSeqHolder info;
   		int status = 0;
   		int istatus =  -1;
   		camera.ackcmd ackdata;
   		long ackHandle = HANDLE_NIL.value;
                int actorIdx = SAL__camera_command_exitControl_ACTOR;

  		// create DataWriter :
  		if (sal[actorIdx].isProcessor == false) {
     			salProcessor(sal[actorIdx].topicName);
     			sal[actorIdx].isProcessor = true;
  		}
  		DataWriter dwriter = getWriter2(SAL__camera_ackcmd_ACTOR);
  		ackcmdDataWriter SALWriter = ackcmdDataWriterHelper.narrow(dwriter);
  		DataReader dreader = getReader(actorIdx);
  		command_exitControlDataReader SALReader = command_exitControlDataReaderHelper.narrow(dreader);
                info = new SampleInfoSeqHolder();
  		istatus = SALReader.take(aCmd, info, 1,ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value, ANY_INSTANCE_STATE.value);
		if (aCmd.value.length > 0) {
   		  if (info.value[0].valid_data) {
    		     if (debugLevel > 8) {
      			System.out.println(  "=== [acceptCommand] exitControl reading a command containing :" );
      			System.out.println(  "    seqNum   : " + aCmd.value[0].private_seqNum );
      			System.out.println(  "    device   : " + aCmd.value[0].device);
      			System.out.println(  "    property : " + aCmd.value[0].property);
      			System.out.println(  "    action   : " + aCmd.value[0].action);
      			System.out.println(  "    value    : " + aCmd.value[0].value);
    		    }
    		    status = aCmd.value[0].private_seqNum;
    		    double rcvdTime = getCurrentTime();
		    double dTime = rcvdTime - aCmd.value[0].private_sndStamp;
    		    if ( dTime < sal[actorIdx].sampleAge ) {
                      ackdata = new camera.ackcmd();
		      ackdata.private_origin = aCmd.value[0].private_origin;
		      ackdata.private_seqNum = aCmd.value[0].private_seqNum;
		      ackdata.error  = 0;
		      ackdata.result = "SAL ACK";
                      data.device    = aCmd.value[0].device;
                      data.property  = aCmd.value[0].property;
                      data.action    = aCmd.value[0].action;
                      data.value     = aCmd.value[0].value;
                      data.state = aCmd.value[0].state;

		      status = aCmd.value[0].private_seqNum;
		      rcvSeqNum = status;
		      rcvOrigin = aCmd.value[0].private_origin;
		      ackdata.ack = SAL__CMD_ACK;

		      istatus = SALWriter.write(ackdata, ackHandle);
		      SALWriter.unregister_instance(ackdata, ackHandle);
  } else {
    		     if (debugLevel > 8) {
      			System.out.println(  "    Old command ignored :   " + dTime );
                     }
                   }
		 }
                } else {
  	           status = 0;
                }
                SALReader.return_loan(aCmd, info);
	        return status;
	}


	public int waitForCompletion_exitControl( int cmdSeqNum , int timeout )
	{
	   int status = 0;
	   int countdown = timeout*1000;
           int actorIdx = SAL__camera_command_exitControl_ACTOR;
	   ackcmdSeqHolder ackcmd = new ackcmdSeqHolder();

	   while (status != SAL__CMD_COMPLETE && countdown != 0) {
	      status = getResponse_exitControl(ackcmd);
	      if (status != SAL__CMD_NOACK) {
	        if (sal[actorIdx].rcvSeqNum != cmdSeqNum) { 
	           status = SAL__CMD_NOACK;
	        }
	      }
	      try
		{
	 	  Thread.sleep(timeout);
		}
		catch(InterruptedException ie)
		{
			// nothing to do
	      }
	      countdown--;
	   }
	   if (status != SAL__CMD_COMPLETE) {
	      if (debugLevel > 0) {
	         System.out.println( "=== [waitForCompletion_exitControl] command " + cmdSeqNum +  " timed out");
	      } 
	      logError(status);
	   } else {
	      if (debugLevel > 0) {
	         System.out.println( "=== [waitForCompletion_exitControl] command " + cmdSeqNum +  " completed ok");
	      } 
           }
 	   return status;
	}


	public int getResponse_exitControl(ackcmdSeqHolder data)
	{
	  int status =  -1;
          int lastsample = 0;
          int actorIdx = SAL__camera_ackcmd_ACTOR;
          int actorIdxCmd = SAL__camera_command_exitControl_ACTOR;

	  DataReader dreader = getReader2(actorIdx);
	  ackcmdDataReader SALReader = ackcmdDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(data, infoSeq, 1, 
					ANY_SAMPLE_STATE.value,
					ANY_VIEW_STATE.value,
					ANY_INSTANCE_STATE.value);
	  if (data.value.length > 0) {
 		for (int i = 0; i < data.value.length; i++) {
                     if ( debugLevel > 8) {
				System.out.println("=== [getResponse_exitControl] message received :");
				System.out.println("    revCode  : "
						+ data.value[i].private_revCode);
		    }
                    lastsample = i;
		}
	 	status = data.value[lastsample].ack;
	  	sal[actorIdxCmd].rcvSeqNum = data.value[lastsample].private_seqNum;
	  	sal[actorIdxCmd].rcvOrigin = data.value[lastsample].private_origin;
	  } else {
                if ( debugLevel > 8) {
	            System.out.println("=== [getResponse_exitControl] No ack yet!"); 
                }
	        status = SAL__CMD_NOACK;
	  }
    	  SALReader.return_loan(data, infoSeq);
	  return status;
	}


	public int ackCommand_exitControl( int cmdId, int ack, int error, String result )
	{
   		int istatus = -1;
   		long ackHandle = HANDLE_NIL.value;
                int actorIdx = SAL__camera_command_exitControl_ACTOR;
                int actorIdx2 = SAL__camera_ackcmd_ACTOR;

   		camera.ackcmd ackdata;
   		DataWriter dwriter = getWriter2(actorIdx2);
   		ackcmdDataWriter SALWriter = ackcmdDataWriterHelper.narrow(dwriter);
                ackdata = new camera.ackcmd();
   		ackdata.private_origin = sal[actorIdx].rcvOrigin;
   		ackdata.private_seqNum = cmdId;
   		ackdata.error = error;
   		ackdata.ack = ack;
   		ackdata.result = result;

   		if (debugLevel > 0) {
      			System.out.println(  "=== [ackCommand_exitControl] acknowledging a command with :" );
      			System.out.println(  "    seqNum   : " + ackdata.private_seqNum );
      			System.out.println(  "    ack      : " + ackdata.ack );
      			System.out.println(  "    error    : " + ackdata.error );
      			System.out.println(  "    result   : " + ackdata.result );
   		}
   		istatus = SALWriter.write(ackdata, ackHandle);
    		SALWriter.unregister_instance(ackdata, ackHandle);

   		return SAL__OK;
	}


	public int issueCommand_enterControl( command_enterControl data )
	{
          Random randGen = new java.util.Random();
  	  long cmdHandle = HANDLE_NIL.value;
          int status;
          int actorIdx = SAL__camera_command_enterControl_ACTOR;
	  if (sal[actorIdx].isCommand == false) {
	     salCommand(sal[actorIdx].topicName);
	     sal[actorIdx].isCommand = true;
	     sal[actorIdx].sndSeqNum = (int)randGen.nextInt(99999999);
	  }
	  DataWriter dwriter = getWriter(actorIdx);	
	  command_enterControlDataWriter SALWriter = command_enterControlDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST COMMAND";
	  data.private_seqNum = sal[actorIdx].sndSeqNum;
          data.private_sndStamp = getCurrentTime();
	  SALWriter.register_instance(data);

	  if (debugLevel > 0) {
	    System.out.println( "=== [issueCommand] enterControl writing a command containing :");
	    System.out.println( data.device + "." + data.property + "." + data.action + " : " + data.value);
	  }
	  status = SALWriter.write(data, cmdHandle);
	  sal[actorIdx].sndSeqNum++;
	  return (sal[actorIdx].sndSeqNum-1);
	}


	public int acceptCommand_enterControl( camera.command_enterControl data )
	{
                command_enterControlSeqHolder aCmd = new command_enterControlSeqHolder();
   		SampleInfoSeqHolder info;
   		int status = 0;
   		int istatus =  -1;
   		camera.ackcmd ackdata;
   		long ackHandle = HANDLE_NIL.value;
                int actorIdx = SAL__camera_command_enterControl_ACTOR;

  		// create DataWriter :
  		if (sal[actorIdx].isProcessor == false) {
     			salProcessor(sal[actorIdx].topicName);
     			sal[actorIdx].isProcessor = true;
  		}
  		DataWriter dwriter = getWriter2(SAL__camera_ackcmd_ACTOR);
  		ackcmdDataWriter SALWriter = ackcmdDataWriterHelper.narrow(dwriter);
  		DataReader dreader = getReader(actorIdx);
  		command_enterControlDataReader SALReader = command_enterControlDataReaderHelper.narrow(dreader);
                info = new SampleInfoSeqHolder();
  		istatus = SALReader.take(aCmd, info, 1,ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value, ANY_INSTANCE_STATE.value);
		if (aCmd.value.length > 0) {
   		  if (info.value[0].valid_data) {
    		     if (debugLevel > 8) {
      			System.out.println(  "=== [acceptCommand] enterControl reading a command containing :" );
      			System.out.println(  "    seqNum   : " + aCmd.value[0].private_seqNum );
      			System.out.println(  "    device   : " + aCmd.value[0].device);
      			System.out.println(  "    property : " + aCmd.value[0].property);
      			System.out.println(  "    action   : " + aCmd.value[0].action);
      			System.out.println(  "    value    : " + aCmd.value[0].value);
    		    }
    		    status = aCmd.value[0].private_seqNum;
    		    double rcvdTime = getCurrentTime();
		    double dTime = rcvdTime - aCmd.value[0].private_sndStamp;
    		    if ( dTime < sal[actorIdx].sampleAge ) {
                      ackdata = new camera.ackcmd();
		      ackdata.private_origin = aCmd.value[0].private_origin;
		      ackdata.private_seqNum = aCmd.value[0].private_seqNum;
		      ackdata.error  = 0;
		      ackdata.result = "SAL ACK";
                      data.device    = aCmd.value[0].device;
                      data.property  = aCmd.value[0].property;
                      data.action    = aCmd.value[0].action;
                      data.value     = aCmd.value[0].value;
                      data.state = aCmd.value[0].state;

		      status = aCmd.value[0].private_seqNum;
		      rcvSeqNum = status;
		      rcvOrigin = aCmd.value[0].private_origin;
		      ackdata.ack = SAL__CMD_ACK;

		      istatus = SALWriter.write(ackdata, ackHandle);
		      SALWriter.unregister_instance(ackdata, ackHandle);
  } else {
    		     if (debugLevel > 8) {
      			System.out.println(  "    Old command ignored :   " + dTime );
                     }
                   }
		 }
                } else {
  	           status = 0;
                }
                SALReader.return_loan(aCmd, info);
	        return status;
	}


	public int waitForCompletion_enterControl( int cmdSeqNum , int timeout )
	{
	   int status = 0;
	   int countdown = timeout*1000;
           int actorIdx = SAL__camera_command_enterControl_ACTOR;
	   ackcmdSeqHolder ackcmd = new ackcmdSeqHolder();

	   while (status != SAL__CMD_COMPLETE && countdown != 0) {
	      status = getResponse_enterControl(ackcmd);
	      if (status != SAL__CMD_NOACK) {
	        if (sal[actorIdx].rcvSeqNum != cmdSeqNum) { 
	           status = SAL__CMD_NOACK;
	        }
	      }
	      try
		{
	 	  Thread.sleep(timeout);
		}
		catch(InterruptedException ie)
		{
			// nothing to do
	      }
	      countdown--;
	   }
	   if (status != SAL__CMD_COMPLETE) {
	      if (debugLevel > 0) {
	         System.out.println( "=== [waitForCompletion_enterControl] command " + cmdSeqNum +  " timed out");
	      } 
	      logError(status);
	   } else {
	      if (debugLevel > 0) {
	         System.out.println( "=== [waitForCompletion_enterControl] command " + cmdSeqNum +  " completed ok");
	      } 
           }
 	   return status;
	}


	public int getResponse_enterControl(ackcmdSeqHolder data)
	{
	  int status =  -1;
          int lastsample = 0;
          int actorIdx = SAL__camera_ackcmd_ACTOR;
          int actorIdxCmd = SAL__camera_command_enterControl_ACTOR;

	  DataReader dreader = getReader2(actorIdx);
	  ackcmdDataReader SALReader = ackcmdDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(data, infoSeq, 1, 
					ANY_SAMPLE_STATE.value,
					ANY_VIEW_STATE.value,
					ANY_INSTANCE_STATE.value);
	  if (data.value.length > 0) {
 		for (int i = 0; i < data.value.length; i++) {
                     if ( debugLevel > 8) {
				System.out.println("=== [getResponse_enterControl] message received :");
				System.out.println("    revCode  : "
						+ data.value[i].private_revCode);
		    }
                    lastsample = i;
		}
	 	status = data.value[lastsample].ack;
	  	sal[actorIdxCmd].rcvSeqNum = data.value[lastsample].private_seqNum;
	  	sal[actorIdxCmd].rcvOrigin = data.value[lastsample].private_origin;
	  } else {
                if ( debugLevel > 8) {
	            System.out.println("=== [getResponse_enterControl] No ack yet!"); 
                }
	        status = SAL__CMD_NOACK;
	  }
    	  SALReader.return_loan(data, infoSeq);
	  return status;
	}


	public int ackCommand_enterControl( int cmdId, int ack, int error, String result )
	{
   		int istatus = -1;
   		long ackHandle = HANDLE_NIL.value;
                int actorIdx = SAL__camera_command_enterControl_ACTOR;
                int actorIdx2 = SAL__camera_ackcmd_ACTOR;

   		camera.ackcmd ackdata;
   		DataWriter dwriter = getWriter2(actorIdx2);
   		ackcmdDataWriter SALWriter = ackcmdDataWriterHelper.narrow(dwriter);
                ackdata = new camera.ackcmd();
   		ackdata.private_origin = sal[actorIdx].rcvOrigin;
   		ackdata.private_seqNum = cmdId;
   		ackdata.error = error;
   		ackdata.ack = ack;
   		ackdata.result = result;

   		if (debugLevel > 0) {
      			System.out.println(  "=== [ackCommand_enterControl] acknowledging a command with :" );
      			System.out.println(  "    seqNum   : " + ackdata.private_seqNum );
      			System.out.println(  "    ack      : " + ackdata.ack );
      			System.out.println(  "    error    : " + ackdata.error );
      			System.out.println(  "    result   : " + ackdata.result );
   		}
   		istatus = SALWriter.write(ackdata, ackHandle);
    		SALWriter.unregister_instance(ackdata, ackHandle);

   		return SAL__OK;
	}


	public int issueCommand_SetValue( command_SetValue data )
	{
          Random randGen = new java.util.Random();
  	  long cmdHandle = HANDLE_NIL.value;
          int status;
          int actorIdx = SAL__camera_command_SetValue_ACTOR;
	  if (sal[actorIdx].isCommand == false) {
	     salCommand(sal[actorIdx].topicName);
	     sal[actorIdx].isCommand = true;
	     sal[actorIdx].sndSeqNum = (int)randGen.nextInt(99999999);
	  }
	  DataWriter dwriter = getWriter(actorIdx);	
	  command_SetValueDataWriter SALWriter = command_SetValueDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST COMMAND";
	  data.private_seqNum = sal[actorIdx].sndSeqNum;
          data.private_sndStamp = getCurrentTime();
	  SALWriter.register_instance(data);

	  if (debugLevel > 0) {
	    System.out.println( "=== [issueCommand] SetValue writing a command containing :");
	    System.out.println( data.device + "." + data.property + "." + data.action + " : " + data.value);
	  }
	  status = SALWriter.write(data, cmdHandle);
	  sal[actorIdx].sndSeqNum++;
	  return (sal[actorIdx].sndSeqNum-1);
	}


	public int acceptCommand_SetValue( camera.command_SetValue data )
	{
                command_SetValueSeqHolder aCmd = new command_SetValueSeqHolder();
   		SampleInfoSeqHolder info;
   		int status = 0;
   		int istatus =  -1;
   		camera.ackcmd ackdata;
   		long ackHandle = HANDLE_NIL.value;
                int actorIdx = SAL__camera_command_SetValue_ACTOR;

  		// create DataWriter :
  		if (sal[actorIdx].isProcessor == false) {
     			salProcessor(sal[actorIdx].topicName);
     			sal[actorIdx].isProcessor = true;
  		}
  		DataWriter dwriter = getWriter2(SAL__camera_ackcmd_ACTOR);
  		ackcmdDataWriter SALWriter = ackcmdDataWriterHelper.narrow(dwriter);
  		DataReader dreader = getReader(actorIdx);
  		command_SetValueDataReader SALReader = command_SetValueDataReaderHelper.narrow(dreader);
                info = new SampleInfoSeqHolder();
  		istatus = SALReader.take(aCmd, info, 1,ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value, ANY_INSTANCE_STATE.value);
		if (aCmd.value.length > 0) {
   		  if (info.value[0].valid_data) {
    		     if (debugLevel > 8) {
      			System.out.println(  "=== [acceptCommand] SetValue reading a command containing :" );
      			System.out.println(  "    seqNum   : " + aCmd.value[0].private_seqNum );
      			System.out.println(  "    device   : " + aCmd.value[0].device);
      			System.out.println(  "    property : " + aCmd.value[0].property);
      			System.out.println(  "    action   : " + aCmd.value[0].action);
      			System.out.println(  "    value    : " + aCmd.value[0].value);
    		    }
    		    status = aCmd.value[0].private_seqNum;
    		    double rcvdTime = getCurrentTime();
		    double dTime = rcvdTime - aCmd.value[0].private_sndStamp;
    		    if ( dTime < sal[actorIdx].sampleAge ) {
                      ackdata = new camera.ackcmd();
		      ackdata.private_origin = aCmd.value[0].private_origin;
		      ackdata.private_seqNum = aCmd.value[0].private_seqNum;
		      ackdata.error  = 0;
		      ackdata.result = "SAL ACK";
                      data.device    = aCmd.value[0].device;
                      data.property  = aCmd.value[0].property;
                      data.action    = aCmd.value[0].action;
                      data.value     = aCmd.value[0].value;
                      data.json_parameters = aCmd.value[0].json_parameters;

		      status = aCmd.value[0].private_seqNum;
		      rcvSeqNum = status;
		      rcvOrigin = aCmd.value[0].private_origin;
		      ackdata.ack = SAL__CMD_ACK;

		      istatus = SALWriter.write(ackdata, ackHandle);
		      SALWriter.unregister_instance(ackdata, ackHandle);
  } else {
    		     if (debugLevel > 8) {
      			System.out.println(  "    Old command ignored :   " + dTime );
                     }
                   }
		 }
                } else {
  	           status = 0;
                }
                SALReader.return_loan(aCmd, info);
	        return status;
	}


	public int waitForCompletion_SetValue( int cmdSeqNum , int timeout )
	{
	   int status = 0;
	   int countdown = timeout*1000;
           int actorIdx = SAL__camera_command_SetValue_ACTOR;
	   ackcmdSeqHolder ackcmd = new ackcmdSeqHolder();

	   while (status != SAL__CMD_COMPLETE && countdown != 0) {
	      status = getResponse_SetValue(ackcmd);
	      if (status != SAL__CMD_NOACK) {
	        if (sal[actorIdx].rcvSeqNum != cmdSeqNum) { 
	           status = SAL__CMD_NOACK;
	        }
	      }
	      try
		{
	 	  Thread.sleep(timeout);
		}
		catch(InterruptedException ie)
		{
			// nothing to do
	      }
	      countdown--;
	   }
	   if (status != SAL__CMD_COMPLETE) {
	      if (debugLevel > 0) {
	         System.out.println( "=== [waitForCompletion_SetValue] command " + cmdSeqNum +  " timed out");
	      } 
	      logError(status);
	   } else {
	      if (debugLevel > 0) {
	         System.out.println( "=== [waitForCompletion_SetValue] command " + cmdSeqNum +  " completed ok");
	      } 
           }
 	   return status;
	}


	public int getResponse_SetValue(ackcmdSeqHolder data)
	{
	  int status =  -1;
          int lastsample = 0;
          int actorIdx = SAL__camera_ackcmd_ACTOR;
          int actorIdxCmd = SAL__camera_command_SetValue_ACTOR;

	  DataReader dreader = getReader2(actorIdx);
	  ackcmdDataReader SALReader = ackcmdDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(data, infoSeq, 1, 
					ANY_SAMPLE_STATE.value,
					ANY_VIEW_STATE.value,
					ANY_INSTANCE_STATE.value);
	  if (data.value.length > 0) {
 		for (int i = 0; i < data.value.length; i++) {
                     if ( debugLevel > 8) {
				System.out.println("=== [getResponse_SetValue] message received :");
				System.out.println("    revCode  : "
						+ data.value[i].private_revCode);
		    }
                    lastsample = i;
		}
	 	status = data.value[lastsample].ack;
	  	sal[actorIdxCmd].rcvSeqNum = data.value[lastsample].private_seqNum;
	  	sal[actorIdxCmd].rcvOrigin = data.value[lastsample].private_origin;
	  } else {
                if ( debugLevel > 8) {
	            System.out.println("=== [getResponse_SetValue] No ack yet!"); 
                }
	        status = SAL__CMD_NOACK;
	  }
    	  SALReader.return_loan(data, infoSeq);
	  return status;
	}


	public int ackCommand_SetValue( int cmdId, int ack, int error, String result )
	{
   		int istatus = -1;
   		long ackHandle = HANDLE_NIL.value;
                int actorIdx = SAL__camera_command_SetValue_ACTOR;
                int actorIdx2 = SAL__camera_ackcmd_ACTOR;

   		camera.ackcmd ackdata;
   		DataWriter dwriter = getWriter2(actorIdx2);
   		ackcmdDataWriter SALWriter = ackcmdDataWriterHelper.narrow(dwriter);
                ackdata = new camera.ackcmd();
   		ackdata.private_origin = sal[actorIdx].rcvOrigin;
   		ackdata.private_seqNum = cmdId;
   		ackdata.error = error;
   		ackdata.ack = ack;
   		ackdata.result = result;

   		if (debugLevel > 0) {
      			System.out.println(  "=== [ackCommand_SetValue] acknowledging a command with :" );
      			System.out.println(  "    seqNum   : " + ackdata.private_seqNum );
      			System.out.println(  "    ack      : " + ackdata.ack );
      			System.out.println(  "    error    : " + ackdata.error );
      			System.out.println(  "    result   : " + ackdata.result );
   		}
   		istatus = SALWriter.write(ackdata, ackHandle);
    		SALWriter.unregister_instance(ackdata, ackHandle);

   		return SAL__OK;
	}


	public int getEvent_ccsConfigured(camera.logevent_ccsConfigured anEvent)
	{
	  int status =  -1;
          int actorIdx = SAL__camera_logevent_ccsConfigured_ACTOR;
          if (sal[actorIdx].subscriber == null) {
             createSubscriber(actorIdx);
             createReader(actorIdx,false);
             sal[actorIdx].isEventReader = true;
          }
          sal[actorIdx].maxSamples=1;
          status = getSample(anEvent);
	  return status;
	}

	public int logEvent_ccsConfigured( camera.logevent_ccsConfigured event, int priority )
	{
	   int status = 0;
           int actorIdx = SAL__camera_logevent_ccsConfigured_ACTOR;
           event.priority=priority;
           if (sal[actorIdx].publisher == null) {
              createPublisher(actorIdx);
              boolean autodispose_unregistered_instances = false;
              createWriter(actorIdx,autodispose_unregistered_instances);
              sal[actorIdx].isEventWriter = true;
           }
           status = putSample(event);
           return status;
	}


	public int getEvent_endInitializeGuider(camera.logevent_endInitializeGuider anEvent)
	{
	  int status =  -1;
          int actorIdx = SAL__camera_logevent_endInitializeGuider_ACTOR;
          if (sal[actorIdx].subscriber == null) {
             createSubscriber(actorIdx);
             createReader(actorIdx,false);
             sal[actorIdx].isEventReader = true;
          }
          sal[actorIdx].maxSamples=1;
          status = getSample(anEvent);
	  return status;
	}

	public int logEvent_endInitializeGuider( camera.logevent_endInitializeGuider event, int priority )
	{
	   int status = 0;
           int actorIdx = SAL__camera_logevent_endInitializeGuider_ACTOR;
           event.priority=priority;
           if (sal[actorIdx].publisher == null) {
              createPublisher(actorIdx);
              boolean autodispose_unregistered_instances = false;
              createWriter(actorIdx,autodispose_unregistered_instances);
              sal[actorIdx].isEventWriter = true;
           }
           status = putSample(event);
           return status;
	}


	public int getEvent_endInitializeImage(camera.logevent_endInitializeImage anEvent)
	{
	  int status =  -1;
          int actorIdx = SAL__camera_logevent_endInitializeImage_ACTOR;
          if (sal[actorIdx].subscriber == null) {
             createSubscriber(actorIdx);
             createReader(actorIdx,false);
             sal[actorIdx].isEventReader = true;
          }
          sal[actorIdx].maxSamples=1;
          status = getSample(anEvent);
	  return status;
	}

	public int logEvent_endInitializeImage( camera.logevent_endInitializeImage event, int priority )
	{
	   int status = 0;
           int actorIdx = SAL__camera_logevent_endInitializeImage_ACTOR;
           event.priority=priority;
           if (sal[actorIdx].publisher == null) {
              createPublisher(actorIdx);
              boolean autodispose_unregistered_instances = false;
              createWriter(actorIdx,autodispose_unregistered_instances);
              sal[actorIdx].isEventWriter = true;
           }
           status = putSample(event);
           return status;
	}


	public int getEvent_endLoadFilter(camera.logevent_endLoadFilter anEvent)
	{
	  int status =  -1;
          int actorIdx = SAL__camera_logevent_endLoadFilter_ACTOR;
          if (sal[actorIdx].subscriber == null) {
             createSubscriber(actorIdx);
             createReader(actorIdx,false);
             sal[actorIdx].isEventReader = true;
          }
          sal[actorIdx].maxSamples=1;
          status = getSample(anEvent);
	  return status;
	}

	public int logEvent_endLoadFilter( camera.logevent_endLoadFilter event, int priority )
	{
	   int status = 0;
           int actorIdx = SAL__camera_logevent_endLoadFilter_ACTOR;
           event.priority=priority;
           if (sal[actorIdx].publisher == null) {
              createPublisher(actorIdx);
              boolean autodispose_unregistered_instances = false;
              createWriter(actorIdx,autodispose_unregistered_instances);
              sal[actorIdx].isEventWriter = true;
           }
           status = putSample(event);
           return status;
	}


	public int getEvent_endReadout(camera.logevent_endReadout anEvent)
	{
	  int status =  -1;
          int actorIdx = SAL__camera_logevent_endReadout_ACTOR;
          if (sal[actorIdx].subscriber == null) {
             createSubscriber(actorIdx);
             createReader(actorIdx,false);
             sal[actorIdx].isEventReader = true;
          }
          sal[actorIdx].maxSamples=1;
          status = getSample(anEvent);
	  return status;
	}

	public int logEvent_endReadout( camera.logevent_endReadout event, int priority )
	{
	   int status = 0;
           int actorIdx = SAL__camera_logevent_endReadout_ACTOR;
           event.priority=priority;
           if (sal[actorIdx].publisher == null) {
              createPublisher(actorIdx);
              boolean autodispose_unregistered_instances = false;
              createWriter(actorIdx,autodispose_unregistered_instances);
              sal[actorIdx].isEventWriter = true;
           }
           status = putSample(event);
           return status;
	}


	public int getEvent_endRotateCarousel(camera.logevent_endRotateCarousel anEvent)
	{
	  int status =  -1;
          int actorIdx = SAL__camera_logevent_endRotateCarousel_ACTOR;
          if (sal[actorIdx].subscriber == null) {
             createSubscriber(actorIdx);
             createReader(actorIdx,false);
             sal[actorIdx].isEventReader = true;
          }
          sal[actorIdx].maxSamples=1;
          status = getSample(anEvent);
	  return status;
	}

	public int logEvent_endRotateCarousel( camera.logevent_endRotateCarousel event, int priority )
	{
	   int status = 0;
           int actorIdx = SAL__camera_logevent_endRotateCarousel_ACTOR;
           event.priority=priority;
           if (sal[actorIdx].publisher == null) {
              createPublisher(actorIdx);
              boolean autodispose_unregistered_instances = false;
              createWriter(actorIdx,autodispose_unregistered_instances);
              sal[actorIdx].isEventWriter = true;
           }
           status = putSample(event);
           return status;
	}


	public int getEvent_endSetFilter(camera.logevent_endSetFilter anEvent)
	{
	  int status =  -1;
          int actorIdx = SAL__camera_logevent_endSetFilter_ACTOR;
          if (sal[actorIdx].subscriber == null) {
             createSubscriber(actorIdx);
             createReader(actorIdx,false);
             sal[actorIdx].isEventReader = true;
          }
          sal[actorIdx].maxSamples=1;
          status = getSample(anEvent);
	  return status;
	}

	public int logEvent_endSetFilter( camera.logevent_endSetFilter event, int priority )
	{
	   int status = 0;
           int actorIdx = SAL__camera_logevent_endSetFilter_ACTOR;
           event.priority=priority;
           if (sal[actorIdx].publisher == null) {
              createPublisher(actorIdx);
              boolean autodispose_unregistered_instances = false;
              createWriter(actorIdx,autodispose_unregistered_instances);
              sal[actorIdx].isEventWriter = true;
           }
           status = putSample(event);
           return status;
	}


	public int getEvent_endShutterClose(camera.logevent_endShutterClose anEvent)
	{
	  int status =  -1;
          int actorIdx = SAL__camera_logevent_endShutterClose_ACTOR;
          if (sal[actorIdx].subscriber == null) {
             createSubscriber(actorIdx);
             createReader(actorIdx,false);
             sal[actorIdx].isEventReader = true;
          }
          sal[actorIdx].maxSamples=1;
          status = getSample(anEvent);
	  return status;
	}

	public int logEvent_endShutterClose( camera.logevent_endShutterClose event, int priority )
	{
	   int status = 0;
           int actorIdx = SAL__camera_logevent_endShutterClose_ACTOR;
           event.priority=priority;
           if (sal[actorIdx].publisher == null) {
              createPublisher(actorIdx);
              boolean autodispose_unregistered_instances = false;
              createWriter(actorIdx,autodispose_unregistered_instances);
              sal[actorIdx].isEventWriter = true;
           }
           status = putSample(event);
           return status;
	}


	public int getEvent_endShutterOpen(camera.logevent_endShutterOpen anEvent)
	{
	  int status =  -1;
          int actorIdx = SAL__camera_logevent_endShutterOpen_ACTOR;
          if (sal[actorIdx].subscriber == null) {
             createSubscriber(actorIdx);
             createReader(actorIdx,false);
             sal[actorIdx].isEventReader = true;
          }
          sal[actorIdx].maxSamples=1;
          status = getSample(anEvent);
	  return status;
	}

	public int logEvent_endShutterOpen( camera.logevent_endShutterOpen event, int priority )
	{
	   int status = 0;
           int actorIdx = SAL__camera_logevent_endShutterOpen_ACTOR;
           event.priority=priority;
           if (sal[actorIdx].publisher == null) {
              createPublisher(actorIdx);
              boolean autodispose_unregistered_instances = false;
              createWriter(actorIdx,autodispose_unregistered_instances);
              sal[actorIdx].isEventWriter = true;
           }
           status = putSample(event);
           return status;
	}


	public int getEvent_endTakeImage(camera.logevent_endTakeImage anEvent)
	{
	  int status =  -1;
          int actorIdx = SAL__camera_logevent_endTakeImage_ACTOR;
          if (sal[actorIdx].subscriber == null) {
             createSubscriber(actorIdx);
             createReader(actorIdx,false);
             sal[actorIdx].isEventReader = true;
          }
          sal[actorIdx].maxSamples=1;
          status = getSample(anEvent);
	  return status;
	}

	public int logEvent_endTakeImage( camera.logevent_endTakeImage event, int priority )
	{
	   int status = 0;
           int actorIdx = SAL__camera_logevent_endTakeImage_ACTOR;
           event.priority=priority;
           if (sal[actorIdx].publisher == null) {
              createPublisher(actorIdx);
              boolean autodispose_unregistered_instances = false;
              createWriter(actorIdx,autodispose_unregistered_instances);
              sal[actorIdx].isEventWriter = true;
           }
           status = putSample(event);
           return status;
	}


	public int getEvent_endUnloadFilter(camera.logevent_endUnloadFilter anEvent)
	{
	  int status =  -1;
          int actorIdx = SAL__camera_logevent_endUnloadFilter_ACTOR;
          if (sal[actorIdx].subscriber == null) {
             createSubscriber(actorIdx);
             createReader(actorIdx,false);
             sal[actorIdx].isEventReader = true;
          }
          sal[actorIdx].maxSamples=1;
          status = getSample(anEvent);
	  return status;
	}

	public int logEvent_endUnloadFilter( camera.logevent_endUnloadFilter event, int priority )
	{
	   int status = 0;
           int actorIdx = SAL__camera_logevent_endUnloadFilter_ACTOR;
           event.priority=priority;
           if (sal[actorIdx].publisher == null) {
              createPublisher(actorIdx);
              boolean autodispose_unregistered_instances = false;
              createWriter(actorIdx,autodispose_unregistered_instances);
              sal[actorIdx].isEventWriter = true;
           }
           status = putSample(event);
           return status;
	}


	public int getEvent_notReadyToTakeImage(camera.logevent_notReadyToTakeImage anEvent)
	{
	  int status =  -1;
          int actorIdx = SAL__camera_logevent_notReadyToTakeImage_ACTOR;
          if (sal[actorIdx].subscriber == null) {
             createSubscriber(actorIdx);
             createReader(actorIdx,false);
             sal[actorIdx].isEventReader = true;
          }
          sal[actorIdx].maxSamples=1;
          status = getSample(anEvent);
	  return status;
	}

	public int logEvent_notReadyToTakeImage( camera.logevent_notReadyToTakeImage event, int priority )
	{
	   int status = 0;
           int actorIdx = SAL__camera_logevent_notReadyToTakeImage_ACTOR;
           event.priority=priority;
           if (sal[actorIdx].publisher == null) {
              createPublisher(actorIdx);
              boolean autodispose_unregistered_instances = false;
              createWriter(actorIdx,autodispose_unregistered_instances);
              sal[actorIdx].isEventWriter = true;
           }
           status = putSample(event);
           return status;
	}


	public int getEvent_prepareToTakeImage(camera.logevent_prepareToTakeImage anEvent)
	{
	  int status =  -1;
          int actorIdx = SAL__camera_logevent_prepareToTakeImage_ACTOR;
          if (sal[actorIdx].subscriber == null) {
             createSubscriber(actorIdx);
             createReader(actorIdx,false);
             sal[actorIdx].isEventReader = true;
          }
          sal[actorIdx].maxSamples=1;
          status = getSample(anEvent);
	  return status;
	}

	public int logEvent_prepareToTakeImage( camera.logevent_prepareToTakeImage event, int priority )
	{
	   int status = 0;
           int actorIdx = SAL__camera_logevent_prepareToTakeImage_ACTOR;
           event.priority=priority;
           if (sal[actorIdx].publisher == null) {
              createPublisher(actorIdx);
              boolean autodispose_unregistered_instances = false;
              createWriter(actorIdx,autodispose_unregistered_instances);
              sal[actorIdx].isEventWriter = true;
           }
           status = putSample(event);
           return status;
	}


	public int getEvent_readyToTakeImage(camera.logevent_readyToTakeImage anEvent)
	{
	  int status =  -1;
          int actorIdx = SAL__camera_logevent_readyToTakeImage_ACTOR;
          if (sal[actorIdx].subscriber == null) {
             createSubscriber(actorIdx);
             createReader(actorIdx,false);
             sal[actorIdx].isEventReader = true;
          }
          sal[actorIdx].maxSamples=1;
          status = getSample(anEvent);
	  return status;
	}

	public int logEvent_readyToTakeImage( camera.logevent_readyToTakeImage event, int priority )
	{
	   int status = 0;
           int actorIdx = SAL__camera_logevent_readyToTakeImage_ACTOR;
           event.priority=priority;
           if (sal[actorIdx].publisher == null) {
              createPublisher(actorIdx);
              boolean autodispose_unregistered_instances = false;
              createWriter(actorIdx,autodispose_unregistered_instances);
              sal[actorIdx].isEventWriter = true;
           }
           status = putSample(event);
           return status;
	}


	public int getEvent_startIntegration(camera.logevent_startIntegration anEvent)
	{
	  int status =  -1;
          int actorIdx = SAL__camera_logevent_startIntegration_ACTOR;
          if (sal[actorIdx].subscriber == null) {
             createSubscriber(actorIdx);
             createReader(actorIdx,false);
             sal[actorIdx].isEventReader = true;
          }
          sal[actorIdx].maxSamples=1;
          status = getSample(anEvent);
	  return status;
	}

	public int logEvent_startIntegration( camera.logevent_startIntegration event, int priority )
	{
	   int status = 0;
           int actorIdx = SAL__camera_logevent_startIntegration_ACTOR;
           event.priority=priority;
           if (sal[actorIdx].publisher == null) {
              createPublisher(actorIdx);
              boolean autodispose_unregistered_instances = false;
              createWriter(actorIdx,autodispose_unregistered_instances);
              sal[actorIdx].isEventWriter = true;
           }
           status = putSample(event);
           return status;
	}


	public int getEvent_startLoadFilter(camera.logevent_startLoadFilter anEvent)
	{
	  int status =  -1;
          int actorIdx = SAL__camera_logevent_startLoadFilter_ACTOR;
          if (sal[actorIdx].subscriber == null) {
             createSubscriber(actorIdx);
             createReader(actorIdx,false);
             sal[actorIdx].isEventReader = true;
          }
          sal[actorIdx].maxSamples=1;
          status = getSample(anEvent);
	  return status;
	}

	public int logEvent_startLoadFilter( camera.logevent_startLoadFilter event, int priority )
	{
	   int status = 0;
           int actorIdx = SAL__camera_logevent_startLoadFilter_ACTOR;
           event.priority=priority;
           if (sal[actorIdx].publisher == null) {
              createPublisher(actorIdx);
              boolean autodispose_unregistered_instances = false;
              createWriter(actorIdx,autodispose_unregistered_instances);
              sal[actorIdx].isEventWriter = true;
           }
           status = putSample(event);
           return status;
	}


	public int getEvent_startReadout(camera.logevent_startReadout anEvent)
	{
	  int status =  -1;
          int actorIdx = SAL__camera_logevent_startReadout_ACTOR;
          if (sal[actorIdx].subscriber == null) {
             createSubscriber(actorIdx);
             createReader(actorIdx,false);
             sal[actorIdx].isEventReader = true;
          }
          sal[actorIdx].maxSamples=1;
          status = getSample(anEvent);
	  return status;
	}

	public int logEvent_startReadout( camera.logevent_startReadout event, int priority )
	{
	   int status = 0;
           int actorIdx = SAL__camera_logevent_startReadout_ACTOR;
           event.priority=priority;
           if (sal[actorIdx].publisher == null) {
              createPublisher(actorIdx);
              boolean autodispose_unregistered_instances = false;
              createWriter(actorIdx,autodispose_unregistered_instances);
              sal[actorIdx].isEventWriter = true;
           }
           status = putSample(event);
           return status;
	}


	public int getEvent_startRotateCarousel(camera.logevent_startRotateCarousel anEvent)
	{
	  int status =  -1;
          int actorIdx = SAL__camera_logevent_startRotateCarousel_ACTOR;
          if (sal[actorIdx].subscriber == null) {
             createSubscriber(actorIdx);
             createReader(actorIdx,false);
             sal[actorIdx].isEventReader = true;
          }
          sal[actorIdx].maxSamples=1;
          status = getSample(anEvent);
	  return status;
	}

	public int logEvent_startRotateCarousel( camera.logevent_startRotateCarousel event, int priority )
	{
	   int status = 0;
           int actorIdx = SAL__camera_logevent_startRotateCarousel_ACTOR;
           event.priority=priority;
           if (sal[actorIdx].publisher == null) {
              createPublisher(actorIdx);
              boolean autodispose_unregistered_instances = false;
              createWriter(actorIdx,autodispose_unregistered_instances);
              sal[actorIdx].isEventWriter = true;
           }
           status = putSample(event);
           return status;
	}


	public int getEvent_startSetFilter(camera.logevent_startSetFilter anEvent)
	{
	  int status =  -1;
          int actorIdx = SAL__camera_logevent_startSetFilter_ACTOR;
          if (sal[actorIdx].subscriber == null) {
             createSubscriber(actorIdx);
             createReader(actorIdx,false);
             sal[actorIdx].isEventReader = true;
          }
          sal[actorIdx].maxSamples=1;
          status = getSample(anEvent);
	  return status;
	}

	public int logEvent_startSetFilter( camera.logevent_startSetFilter event, int priority )
	{
	   int status = 0;
           int actorIdx = SAL__camera_logevent_startSetFilter_ACTOR;
           event.priority=priority;
           if (sal[actorIdx].publisher == null) {
              createPublisher(actorIdx);
              boolean autodispose_unregistered_instances = false;
              createWriter(actorIdx,autodispose_unregistered_instances);
              sal[actorIdx].isEventWriter = true;
           }
           status = putSample(event);
           return status;
	}


	public int getEvent_startShutterClose(camera.logevent_startShutterClose anEvent)
	{
	  int status =  -1;
          int actorIdx = SAL__camera_logevent_startShutterClose_ACTOR;
          if (sal[actorIdx].subscriber == null) {
             createSubscriber(actorIdx);
             createReader(actorIdx,false);
             sal[actorIdx].isEventReader = true;
          }
          sal[actorIdx].maxSamples=1;
          status = getSample(anEvent);
	  return status;
	}

	public int logEvent_startShutterClose( camera.logevent_startShutterClose event, int priority )
	{
	   int status = 0;
           int actorIdx = SAL__camera_logevent_startShutterClose_ACTOR;
           event.priority=priority;
           if (sal[actorIdx].publisher == null) {
              createPublisher(actorIdx);
              boolean autodispose_unregistered_instances = false;
              createWriter(actorIdx,autodispose_unregistered_instances);
              sal[actorIdx].isEventWriter = true;
           }
           status = putSample(event);
           return status;
	}


	public int getEvent_startShutterOpen(camera.logevent_startShutterOpen anEvent)
	{
	  int status =  -1;
          int actorIdx = SAL__camera_logevent_startShutterOpen_ACTOR;
          if (sal[actorIdx].subscriber == null) {
             createSubscriber(actorIdx);
             createReader(actorIdx,false);
             sal[actorIdx].isEventReader = true;
          }
          sal[actorIdx].maxSamples=1;
          status = getSample(anEvent);
	  return status;
	}

	public int logEvent_startShutterOpen( camera.logevent_startShutterOpen event, int priority )
	{
	   int status = 0;
           int actorIdx = SAL__camera_logevent_startShutterOpen_ACTOR;
           event.priority=priority;
           if (sal[actorIdx].publisher == null) {
              createPublisher(actorIdx);
              boolean autodispose_unregistered_instances = false;
              createWriter(actorIdx,autodispose_unregistered_instances);
              sal[actorIdx].isEventWriter = true;
           }
           status = putSample(event);
           return status;
	}


	public int getEvent_startUnloadFilter(camera.logevent_startUnloadFilter anEvent)
	{
	  int status =  -1;
          int actorIdx = SAL__camera_logevent_startUnloadFilter_ACTOR;
          if (sal[actorIdx].subscriber == null) {
             createSubscriber(actorIdx);
             createReader(actorIdx,false);
             sal[actorIdx].isEventReader = true;
          }
          sal[actorIdx].maxSamples=1;
          status = getSample(anEvent);
	  return status;
	}

	public int logEvent_startUnloadFilter( camera.logevent_startUnloadFilter event, int priority )
	{
	   int status = 0;
           int actorIdx = SAL__camera_logevent_startUnloadFilter_ACTOR;
           event.priority=priority;
           if (sal[actorIdx].publisher == null) {
              createPublisher(actorIdx);
              boolean autodispose_unregistered_instances = false;
              createWriter(actorIdx,autodispose_unregistered_instances);
              sal[actorIdx].isEventWriter = true;
           }
           status = putSample(event);
           return status;
	}


	public int getEvent_SettingVersions(camera.logevent_SettingVersions anEvent)
	{
	  int status =  -1;
          int actorIdx = SAL__camera_logevent_SettingVersions_ACTOR;
          if (sal[actorIdx].subscriber == null) {
             createSubscriber(actorIdx);
             createReader(actorIdx,false);
             sal[actorIdx].isEventReader = true;
          }
          sal[actorIdx].maxSamples=1;
          status = getSample(anEvent);
	  return status;
	}

	public int logEvent_SettingVersions( camera.logevent_SettingVersions event, int priority )
	{
	   int status = 0;
           int actorIdx = SAL__camera_logevent_SettingVersions_ACTOR;
           event.priority=priority;
           if (sal[actorIdx].publisher == null) {
              createPublisher(actorIdx);
              boolean autodispose_unregistered_instances = false;
              createWriter(actorIdx,autodispose_unregistered_instances);
              sal[actorIdx].isEventWriter = true;
           }
           status = putSample(event);
           return status;
	}


	public int getEvent_SummaryState(camera.logevent_SummaryState anEvent)
	{
	  int status =  -1;
          int actorIdx = SAL__camera_logevent_SummaryState_ACTOR;
          if (sal[actorIdx].subscriber == null) {
             createSubscriber(actorIdx);
             createReader(actorIdx,false);
             sal[actorIdx].isEventReader = true;
          }
          sal[actorIdx].maxSamples=1;
          status = getSample(anEvent);
	  return status;
	}

	public int logEvent_SummaryState( camera.logevent_SummaryState event, int priority )
	{
	   int status = 0;
           int actorIdx = SAL__camera_logevent_SummaryState_ACTOR;
           event.priority=priority;
           if (sal[actorIdx].publisher == null) {
              createPublisher(actorIdx);
              boolean autodispose_unregistered_instances = false;
              createWriter(actorIdx,autodispose_unregistered_instances);
              sal[actorIdx].isEventWriter = true;
           }
           status = putSample(event);
           return status;
	}


	public int getEvent_ErrorCode(camera.logevent_ErrorCode anEvent)
	{
	  int status =  -1;
          int actorIdx = SAL__camera_logevent_ErrorCode_ACTOR;
          if (sal[actorIdx].subscriber == null) {
             createSubscriber(actorIdx);
             createReader(actorIdx,false);
             sal[actorIdx].isEventReader = true;
          }
          sal[actorIdx].maxSamples=1;
          status = getSample(anEvent);
	  return status;
	}

	public int logEvent_ErrorCode( camera.logevent_ErrorCode event, int priority )
	{
	   int status = 0;
           int actorIdx = SAL__camera_logevent_ErrorCode_ACTOR;
           event.priority=priority;
           if (sal[actorIdx].publisher == null) {
              createPublisher(actorIdx);
              boolean autodispose_unregistered_instances = false;
              createWriter(actorIdx,autodispose_unregistered_instances);
              sal[actorIdx].isEventWriter = true;
           }
           status = putSample(event);
           return status;
	}


	public int getEvent_AppliedSettingsMatchStart(camera.logevent_AppliedSettingsMatchStart anEvent)
	{
	  int status =  -1;
          int actorIdx = SAL__camera_logevent_AppliedSettingsMatchStart_ACTOR;
          if (sal[actorIdx].subscriber == null) {
             createSubscriber(actorIdx);
             createReader(actorIdx,false);
             sal[actorIdx].isEventReader = true;
          }
          sal[actorIdx].maxSamples=1;
          status = getSample(anEvent);
	  return status;
	}

	public int logEvent_AppliedSettingsMatchStart( camera.logevent_AppliedSettingsMatchStart event, int priority )
	{
	   int status = 0;
           int actorIdx = SAL__camera_logevent_AppliedSettingsMatchStart_ACTOR;
           event.priority=priority;
           if (sal[actorIdx].publisher == null) {
              createPublisher(actorIdx);
              boolean autodispose_unregistered_instances = false;
              createWriter(actorIdx,autodispose_unregistered_instances);
              sal[actorIdx].isEventWriter = true;
           }
           status = putSample(event);
           return status;
	}


        public int getActorIndex (String topicName) {
          for (int i=0; i<SAL__ACTORS_MAXCOUNT;i++) {
             if ( topicName.length() == sal[i].topicName.length() )  {
                if ( topicName.equals(sal[i].topicName) )  {
                   return i;
                }
             }
          }
          return SAL__ERROR;
        }


	public int salTelemetryPub(String topicName)
	{
	  int actorIdx = -1;
	  int status = 0;

	  actorIdx = getActorIndex(topicName);
	  if (actorIdx > -1) {
	     salTelemetryPub(actorIdx);
	  } else {
	     status = SAL__ERROR;
	  }
	  return status;
	}

	public int salTelemetrySub(String topicName)
	{
	  int actorIdx = -1;
	  int status = 0;

	  actorIdx = getActorIndex(topicName);
	  if (actorIdx > -1) {
	     salTelemetrySub(actorIdx);
	  } else {
	     status = SAL__ERROR;
	  }
	  return status;
	}


        public void salTelemetryPub(int actorIdx) {
		String partitionName = domainName;

		// create Domain Participant
		createParticipant(partitionName);

		// create Type
		salTypeSupport(actorIdx);

		// create Topic
		createTopic(actorIdx);

		// create Publisher
		createPublisher(actorIdx);

		// create DataWriter
		createWriter(actorIdx,false);
		sal[actorIdx].isWriter = true;
        }




        public void salTelemetrySub(int actorIdx) {
		String partitionName = domainName;
		// create Domain Participant
		createParticipant(partitionName);

		// create Type
		salTypeSupport(actorIdx);
		// create Type

		// create Topic
		createTopic(actorIdx);

		// create Subscriber
		createSubscriber(actorIdx);

		// create DataReader
		createReader(actorIdx,false);
                sal[actorIdx].isReader = true;
	}



	public void logError(int status) 
	{
		System.out.println("=== ERROR return value = " + status); 
	}

        
        public void salInitialize()
	{
                String dname = System.getenv("LSST_DDS_DOMAIN");
                if (dname != null) {
                   domainName = dname;
                } else {
                   domainName = "LSST";
                }
		hasReader = false;
		hasWriter = false;
		debugLevel = 1;
		hasCommand = false;
		hasProcessor = false;
		hasEventReader = false;
		hasEventWriter = false;
		subsystemID = 0;
                rcvOrigin = 0;
	}

	public SAL_camera()
	{
                String dname = System.getenv("LSST_DDS_DOMAIN");
                if (dname != null) {
                   domainName = dname;
                } else {
                   domainName = "LSST";
                }
		hasReader = false;
		hasWriter = false;
		hasCommand = false;
		hasEventReader = false;
		hasEventWriter = false;
		hasProcessor = false;
		subsystemID = 0;
		debugLevel = 1;
                rcvOrigin = 0;
                initSalActors();
	}

	public double getCurrentTime()
	{
		long ms = System.currentTimeMillis();
  		double ts = (double)ms / 1000.0;
		return ts;
	}

	public int issueCommand( command data )
	{
  	  long cmdHandle = HANDLE_NIL.value;
          int status;
	  if (!hasWriter) {
	     createWriter(false);
	     hasWriter = true;
	     sndSeqNum = 1;
	  }
	  DataWriter dwriter = getWriter();	
	  commandDataWriter SALWriter = commandDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST COMMAND";
	  data.private_seqNum = sndSeqNum;
	  SALWriter.register_instance(data);
	  if (debugLevel > 0) {
	    System.out.println( "=== [issueCommand] writing a command containing :");
	    System.out.println( " " + data.device + "." + data.property + "." + data.action + " : " + data.value);
	  }
	  status = SALWriter.write(data, cmdHandle);
	  sndSeqNum++;
	  return (sndSeqNum-1);
	}

	public int ackCommand( int cmdId, int ack, int error, String result )
	{
   		int istatus = -1;
   		long ackHandle = HANDLE_NIL.value;

   		camera.ackcmd ackdata;
   		DataWriter dwriter = getWriter2();
   		ackcmdDataWriter SALWriter = ackcmdDataWriterHelper.narrow(dwriter);
                ackdata = new camera.ackcmd();
   		ackdata.private_origin = rcvOrigin;
   		ackdata.private_seqNum = rcvSeqNum;
   		ackdata.error = error;
   		ackdata.ack = ack;
   		ackdata.result = result;
   		if (debugLevel > 0) {
      			System.out.println(  "=== [ackCommand] acknowledging a command with :" );
      			System.out.println(  "    seqNum   : " + ackdata.private_seqNum );
      			System.out.println(  "    ack      : " + ackdata.ack );
      			System.out.println(  "    error    : " + ackdata.error );
      			System.out.println(  "    result   : " + ackdata.result );
   		}
   		istatus = SALWriter.write(ackdata, ackHandle);
   		return SAL__OK;
	}



	public int acceptCommand( camera.command data )
	{
                commandSeqHolder aCmd = new commandSeqHolder();
   		SampleInfoSeqHolder info;
   		int status = 0;
   		int istatus =  -1;
   		camera.ackcmd ackdata;;
   		long ackHandle = HANDLE_NIL.value;

  		// create DataWriter :
  		// If autodispose_unregistered_instances is set to true (default value),
  		// you will have to start the subscriber before the publisher
  		boolean autodispose_unregistered_instances = false;
  		if (!hasWriter) {
     			createWriter2(autodispose_unregistered_instances);
     			hasWriter = true;
  		}
  		DataWriter dwriter = getWriter2();
  		ackcmdDataWriter SALWriter = ackcmdDataWriterHelper.narrow(dwriter);
  		DataReader dreader = getReader();
  		commandDataReader SALReader = commandDataReaderHelper.narrow(dreader);
                info = new SampleInfoSeqHolder();
  		istatus = SALReader.take(aCmd, info, 1,ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value, ANY_INSTANCE_STATE.value);
		if (aCmd.value.length > 0) {
   		  if (info.value[0].valid_data) {
    		     if (debugLevel > 0) {
      			System.out.println(  "=== [acceptCommand] reading a command containing :" );
      			System.out.println(  "    seqNum   : " + aCmd.value[0].private_seqNum );
      			System.out.println(  "    device   : " + aCmd.value[0].device);
      			System.out.println(  "    property : " + aCmd.value[0].property);
      			System.out.println(  "    action   : " + aCmd.value[0].action);
      			System.out.println(  "    value    : " + aCmd.value[0].value);
      			System.out.println(  "    modifiers: " + aCmd.value[0].modifiers);
    		    }
                    ackdata = new camera.ackcmd();
		    ackdata.private_origin = aCmd.value[0].private_origin;
		    ackdata.private_seqNum = aCmd.value[0].private_seqNum;
		    ackdata.error  = 0;
		    ackdata.result = "SAL ACK";
                    data.device    = aCmd.value[0].device;
                    data.property  = aCmd.value[0].property;
                    data.action    = aCmd.value[0].action;
                    data.value     = aCmd.value[0].value;
                    data.modifiers = aCmd.value[0].modifiers;
		    status = aCmd.value[0].private_seqNum;
		    rcvSeqNum = status;
		    rcvOrigin = aCmd.value[0].private_origin;
		    ackdata.ack = SAL__CMD_ACK;
		    SALReader.return_loan(aCmd, info);
		    istatus = SALWriter.write(ackdata, ackHandle);
		 }
	     } else {
	        status = 0;
	     }
	     return status;
	}

// INSERT CMDALIAS SUPPORT  for issueCommand and acceptCommand  


	public int checkCommand( int cmdSeqNum )
	{
	   int status;
	   ackcmdSeqHolder ackcmd = new ackcmdSeqHolder();
	   status = getResponse(ackcmd);
	   return status;
	}

	public int getResponse(ackcmdSeqHolder data)
	{
	  int status =  -1;
          int lastsample = 0;

	  DataReader dreader = getReader2();
	  ackcmdDataReader SALReader = ackcmdDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(data, infoSeq, 1,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ANY_INSTANCE_STATE.value);
	  if (data.value.length > 0) {
 		for (int i = 0; i < data.value.length; i++) {
                     if ( debugLevel > 0) {
				System.out.println("=== [getResponse] message received :");
				System.out.println("    revCode  : "
						+ data.value[i].private_revCode);
		    }
                    lastsample = i;
		}
	 	status = data.value[lastsample].ack;
	  	rcvSeqNum = data.value[lastsample].private_seqNum;
	  	rcvOrigin = data.value[lastsample].private_origin;
	  } else {
	        System.out.println("=== [getResponse] No ack yet!"); 
	        status = SAL__CMD_NOACK;
	  }
    	  SALReader.return_loan(data, infoSeq);
	  return status;
	}

	public int cancelCommand( int cmdSeqNum )
	{
	   int status = 0;
	   return status;
	}


	public int abortCommand( int cmdSeqNum )
	{
	   int status = 0;
	   return status;
	}

        public static final int SAL__SLOWPOLL= 		   1;
        public static final int SAL__OK = 		   0;
        public static final int SAL__ERR = 		  -1;
        public static final int SAL__ERROR = 		  -1;
        public static final int SAL__NO_UPDATES = 	-100;
        public static final int SAL__LOG_ROUTINES = 	   1;
        public static final int SAL__CMD_ACK =      	 300;
        public static final int SAL__CMD_INPROGRESS = 	 301;
        public static final int SAL__CMD_STALLED =    	 302;
        public static final int SAL__CMD_COMPLETE =   	 303;
        public static final int SAL__CMD_NOPERM =   	-300;
        public static final int SAL__CMD_NOACK =    	-301;
        public static final int SAL__CMD_FAILED =   	-302;
        public static final int SAL__CMD_ABORTED =  	-303;
        public static final int SAL__CMD_TIMEOUT =  	-304;
        public static final int SAL__DATA_AVAIL	=	400;
        public static final int SAL__DEADLINE_MISS =	401;
        public static final int SAL__INCOMPAT_QOS =	402;
        public static final int SAL__SAMPLE_REJ	=	403;
        public static final int SAL__LIVELINESS_CHG =	404;
        public static final int SAL__SAMPLELOST	=	405;
        public static final int SAL__SUBSCR_MATCH =	406;
        public static final int SAL__STANDBYSTATE =	500;
        public static final int SAL__DISABLEDSTATE =	510;
        public static final int SAL__ENABLEDSTATE =	520;
        public static final int SAL__OFFLINESTATE =	530;
        public static final int SAL__PUBLISHONLYSTATE =	531;
        public static final int SAL__AVAILABLESTATE =	532;
        public static final int SAL__FAULTSTATE	=	540;


	public int waitForCompletion( int cmdSeqNum , int timeout )
	{
	   int status = 0;
	   int countdown = timeout;
	   ackcmdSeqHolder ackcmd = new ackcmdSeqHolder();

	   while (status != SAL__CMD_COMPLETE && countdown != 0) {
	      status = getResponse(ackcmd);
	      if (status != SAL__CMD_NOACK) {
	        if (rcvSeqNum != cmdSeqNum) { 
	           status = SAL__CMD_NOACK;
	        }
	      }
	      try
		{
	 	  Thread.sleep(100*timeout);
		}
		catch(InterruptedException ie)
		{
			// nothing to do
	      }
	      System.out.println( "=== [waitForCompletion] command " + cmdSeqNum +  " countdown = " + countdown);
	      countdown--;
	   }
	   if (status != SAL__CMD_COMPLETE) {
	      if (debugLevel > 0) {
	         System.out.println( "=== [waitForCompletion] command " + cmdSeqNum +  " timed out");
	      } 
	      logError(status);
	   } else {
	      if (debugLevel > 0) {
	         System.out.println( "=== [waitForCompletion] command " + cmdSeqNum +  " completed ok");
	      } 
           }
 	   return status;
	}


	public int getEvent(camera.logevent anEvent)
	{
	  int status =  -1;
	  int actorIdx = SAL__camera_logevent_ACTOR; 
	  if (sal[actorIdx].isEventReader == false) {
	     salTelemetrySub("camera_logevent");
	     sal[actorIdx].isEventReader = true;
	  }
	  DataReader dreader = getReader(actorIdx);
	  logeventDataReader SALReader = logeventDataReaderHelper.narrow(dreader);
          logeventSeqHolder data = new logeventSeqHolder();
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(data, infoSeq, 1,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ANY_INSTANCE_STATE.value);
          if (data.value.length > 0) {
  	     if (infoSeq.value[0].valid_data) {
		for (int i = 0; i < data.value.length; i++) {
		  if (debugLevel > 0) {
				System.out.println("=== [getEvent] message received :");
				System.out.println("    revCode  : "
						+ data.value[i].private_revCode);
                  }
		}
                anEvent.message = data.value[0].message;
                status = SAL__OK;
             } else {
                status = SAL__NO_UPDATES;
             }
	  } else {
             status = SAL__NO_UPDATES;
          }
          SALReader.return_loan(data,infoSeq);
	  return status;
	}

	public int logEvent( String message, int priority )
	{
	   int status = 0;
	   int actorIdx = SAL__camera_logevent_ACTOR; 
	   int istatus =  -1;
	   camera.logevent event;
	   String stopic="camera_logevent";
	   long eventHandle = HANDLE_NIL.value;

	  if (sal[actorIdx].isEventWriter == false) {
	    salTelemetryPub(stopic);
	    sal[actorIdx].isEventWriter = true;	
  	  }
	  DataWriter dwriter = getWriter(actorIdx);
	  logeventDataWriter SALWriter = logeventDataWriterHelper.narrow(dwriter);
          event = new camera.logevent();
	  event.message = message;
	  status=SALWriter.write(event, eventHandle);
	  checkStatus(status, "logEventDataWriter.write");
	  SALWriter.dispose(event, eventHandle);
	   return status;
	}

// INSERT EVENTALIAS SUPPORT



	public int setDebugLevel( int level )
	{
           int status = 0;
	   debugLevel = level;
	   return status;	
	}

	public int getDebugLevel( int level )
	{
	   return debugLevel;
	}

	public int getOrigin()
	{
	   int status = 0;
	   return status;
	}

	public int getProperty(String property, String value)
	{
	   int status = SAL__OK;
	   value = "UNKNOWN";
	   if (status != SAL__OK) {
	      if (debugLevel >= SAL__LOG_ROUTINES) {
	          logError(status);
	      }
	   }
	   return status;
	}

	public int setProperty(String property, String value)
	{
           int status = SAL__OK;
	   if (status != SAL__OK) {
	      if (debugLevel >= SAL__LOG_ROUTINES) {
	          logError(status);
	      }
	   }
	   return status;
	}
 

	public void salCommand()
	{
	  String stopic1="keyedCommand";
	  String stopic2="keyedResponse";
	  String scommand="camera_command";
	  String sresponse="camera_ackcmd";

	  // create domain participant
	  createParticipant(domainName);

	  //create Publisher
	  createPublisher();
	  createSubscriber();

	  //create types
	  commandTypeSupport mt = new commandTypeSupport();
	  registerType(mt);
	  ackcmdTypeSupport mtr = new ackcmdTypeSupport();
	  registerType2(mtr);

	  //create Topics
	  createTopic(scommand);
	  createTopic2(sresponse);
	
	  //create a reader for responses
	  createReader2(false);
	  hasReader = true;
	  hasCommand = true;
	}


	public void salCommand(String cmdAlias)
	{
          int actorIdx = getActorIndex(cmdAlias);
	  String stopic1="keyedCommand";
	  String stopic2="keyedResponse";
	  String sresponse="camera_ackcmd";

	  // create domain participant
	  createParticipant(domainName);

	  //create Publisher
	  createPublisher(actorIdx);
	  createSubscriber(SAL__camera_ackcmd_ACTOR);

	  //create types
	  salTypeSupport(actorIdx);
	  ackcmdTypeSupport mtr = new ackcmdTypeSupport();
	  registerType2(SAL__camera_ackcmd_ACTOR,mtr);

	  //create Topics
	  createTopic(actorIdx,cmdAlias);
	  createTopic2(SAL__camera_ackcmd_ACTOR,sresponse);
	
	  //create a reader for responses
	  createReader2(SAL__camera_ackcmd_ACTOR,false);
	  sal[actorIdx].isReader = true;
	  boolean autodispose_unregistered_instances = false;
	  createWriter(actorIdx,autodispose_unregistered_instances);
	  sal[actorIdx].isWriter = true;
	  sal[actorIdx].isCommand = true;
          sal[actorIdx].sndSeqNum = (int)getCurrentTime();
          sal[SAL__camera_ackcmd_ACTOR].sampleAge = 1.0;
	}



	public void salProcessor()
	{
	  String stopic1="keyedCommand";
	  String stopic2="keyedResponse";
	  String scommand="camera_command";
	  String sresponse="camera_ackcmd";

	  // create domain participant
	  createParticipant(domainName);

	  //create Publisher
	  createPublisher();
	  createSubscriber();

	  //create types
	  commandTypeSupport mt = new commandTypeSupport();
	  registerType(mt);
	  ackcmdTypeSupport mtr = new ackcmdTypeSupport();
	  registerType2(mtr);

	  //create Topics
	  createTopic(scommand);
	  createTopic2(sresponse);

	  //create a reader for commands
	  createReader(false);
	  boolean autodispose_unregistered_instances = false;
	  createWriter2(autodispose_unregistered_instances);
	  hasWriter = true;
	  hasProcessor = true;
	}


	public void salProcessor(String cmdAlias)
	{
          int actorIdx = getActorIndex(cmdAlias);
	  String stopic1="keyedCommand";
	  String stopic2="keyedResponse";
	  String sresponse="camera_ackcmd";

	  // create domain participant
	  createParticipant(domainName);

	  //create Publisher
	  createPublisher(SAL__camera_ackcmd_ACTOR);
	  createSubscriber(actorIdx);

	  //create types
	  salTypeSupport(actorIdx);
	  ackcmdTypeSupport mtr = new ackcmdTypeSupport();
	  registerType2(SAL__camera_ackcmd_ACTOR,mtr);

	  //create Topics
	  createTopic(actorIdx,cmdAlias);
	  createTopic2(SAL__camera_ackcmd_ACTOR,sresponse);

	  //create a reader for commands
	  createReader(actorIdx,false);
	  boolean autodispose_unregistered_instances = false;
	  createWriter2(SAL__camera_ackcmd_ACTOR,autodispose_unregistered_instances);
	  sal[actorIdx].isWriter = true;
	  sal[actorIdx].isProcessor = true;
          sal[actorIdx].sampleAge = 1.0;
	}

	public void salShutdown()
	{
          if (participant != null) {
            participant.delete_contained_entities();
  	    deleteParticipant();
          }
	}

	public int salEvent(String topicName)
	{
                int actorIdx = getActorIndex(topicName);
                if ( actorIdx < 0) {return SAL__ERROR;}

		String partitionName = domainName;

		// create Domain Participant
		createParticipant(partitionName);

		// create Type
		salTypeSupport(actorIdx);

		// create Topic
		createTopic(actorIdx);
                return SAL__OK;
	}

	public void createParticipant(String partitionName) {
           if (participant == null) {
		dpf = DomainParticipantFactory.get_instance();
		checkHandle(dpf, "DomainParticipantFactory.get_instance");

		participant = dpf.create_participant(DOMAIN_ID_DEFAULT.value,
				PARTICIPANT_QOS_DEFAULT.value, null, STATUS_MASK_NONE.value);
		checkHandle(dpf,
				"DomainParticipantFactory.create_participant");
		this.partitionName = partitionName;
           }
	}

	public void deleteParticipant() {
		dpf.delete_participant(participant);
	}

	public void registerType(TypeSupportImpl ts) {
		typeName = ts.get_type_name();
		int status = ts.register_type(participant, typeName);
		checkStatus(status, "register_type");
	}

	public void registerType2(TypeSupportImpl ts) {
		typeName2 = ts.get_type_name();
		int status = ts.register_type(participant, typeName2);
		checkStatus(status, "register_type");
	}

	public void registerType(int actorIdx, TypeSupportImpl ts) {
		sal[actorIdx].typeName = ts.get_type_name();
		int status = ts.register_type(participant, sal[actorIdx].typeName);
		checkStatus(status, "register_type");
	}

	public void registerType2(int actorIdx,TypeSupportImpl ts) {
		sal[actorIdx].typeName2 = ts.get_type_name();
		int status = ts.register_type(participant, sal[actorIdx].typeName2);
		checkStatus(status, "register_type");
	}



	public void createTopic(String topicName) {
		int status = -1;
		participant.get_default_topic_qos(topicQos);
		topicQos.value.reliability.kind = ReliabilityQosPolicyKind.RELIABLE_RELIABILITY_QOS;
		topicQos.value.durability.kind = DurabilityQosPolicyKind.TRANSIENT_DURABILITY_QOS;
		topicQos.value.history.kind = HistoryQosPolicyKind.KEEP_LAST_HISTORY_QOS;
		topicQos.value.history.depth = 10000;
		status = participant.set_default_topic_qos(topicQos.value);
		checkStatus(status,
				"DomainParticipant.set_default_topic_qos");
		System.out.println("=== [createTopic] : topicName " + topicName + " type = " + typeName);
		topic = participant.create_topic(topicName, typeName, topicQos.value,
				null, STATUS_MASK_NONE.value);
		checkHandle(topic, "DomainParticipant.create_topic");
	}

	public void createTopic2(String topicName) {
		int status = -1;
		participant.get_default_topic_qos(topicQos2);
		topicQos2.value.reliability.kind = ReliabilityQosPolicyKind.RELIABLE_RELIABILITY_QOS;
		topicQos2.value.durability.kind = DurabilityQosPolicyKind.TRANSIENT_DURABILITY_QOS;
		topicQos2.value.history.kind = HistoryQosPolicyKind.KEEP_LAST_HISTORY_QOS;
		topicQos2.value.history.depth = 10000;
		status = participant.set_default_topic_qos(topicQos2.value);
		checkStatus(status,
				"DomainParticipant.set_default_topic_qos");
		System.out.println("=== [createTopic2] : topicName " + topicName + " type = " + typeName2);

		topic2 = participant.create_topic(topicName, typeName2, topicQos2.value,
				null, STATUS_MASK_NONE.value);
		checkHandle(topic2, "DomainParticipant.create_topic");
	}


	public void createTopic(int actorIdx) {
		int status = -1;
		participant.get_default_topic_qos(sal[actorIdx].topicQos);
		sal[actorIdx].topicQos.value.reliability.kind = ReliabilityQosPolicyKind.RELIABLE_RELIABILITY_QOS;
		sal[actorIdx].topicQos.value.durability.kind = DurabilityQosPolicyKind.TRANSIENT_DURABILITY_QOS;
		sal[actorIdx].topicQos.value.history.kind = HistoryQosPolicyKind.KEEP_LAST_HISTORY_QOS;
		sal[actorIdx].topicQos.value.history.depth = 10000;
		status = participant.set_default_topic_qos(sal[actorIdx].topicQos.value);
		checkStatus(status,
				"DomainParticipant.set_default_topic_qos");
		System.out.println("=== [createTopic] : topicName " + sal[actorIdx].topicName + " type = " + sal[actorIdx].typeName);
		sal[actorIdx].topic = participant.create_topic(sal[actorIdx].topicName, sal[actorIdx].typeName, sal[actorIdx].topicQos.value,
				null, STATUS_MASK_NONE.value);
		checkHandle(sal[actorIdx].topic, "DomainParticipant.create_topic");
	}

	public void createTopic2(int actorIdx) {
		int status = -1;
		participant.get_default_topic_qos(sal[actorIdx].topicQos2);
		sal[actorIdx].topicQos2.value.reliability.kind = ReliabilityQosPolicyKind.RELIABLE_RELIABILITY_QOS;
		sal[actorIdx].topicQos2.value.durability.kind = DurabilityQosPolicyKind.TRANSIENT_DURABILITY_QOS;
		sal[actorIdx].topicQos2.value.history.kind = HistoryQosPolicyKind.KEEP_LAST_HISTORY_QOS;
		sal[actorIdx].topicQos2.value.history.depth = 10000;
		status = participant.set_default_topic_qos(sal[actorIdx].topicQos2.value);
		checkStatus(status,
				"DomainParticipant.set_default_topic_qos");
		System.out.println("=== [createTopic2] : topicName " + sal[actorIdx].topicName + " type = " + sal[actorIdx].typeName2);

		sal[actorIdx].topic2 = participant.create_topic(sal[actorIdx].topicName, sal[actorIdx].typeName2, sal[actorIdx].topicQos2.value,
				null, STATUS_MASK_NONE.value);
		checkHandle(sal[actorIdx].topic2, "DomainParticipant.create_topic");
	}

	public void createTopic(int actorIdx, String topicName) {
		int status = -1;
		participant.get_default_topic_qos(sal[actorIdx].topicQos);
		sal[actorIdx].topicQos.value.reliability.kind = ReliabilityQosPolicyKind.RELIABLE_RELIABILITY_QOS;
		sal[actorIdx].topicQos.value.durability.kind = DurabilityQosPolicyKind.TRANSIENT_DURABILITY_QOS;
		sal[actorIdx].topicQos.value.history.kind = HistoryQosPolicyKind.KEEP_LAST_HISTORY_QOS;
		sal[actorIdx].topicQos.value.history.depth = 10000;
		status = participant.set_default_topic_qos(sal[actorIdx].topicQos.value);
		checkStatus(status,
				"DomainParticipant.set_default_topic_qos");
		System.out.println("=== [createTopic] : topicName " + topicName + " type = " + sal[actorIdx].typeName);
		sal[actorIdx].topic = participant.create_topic(topicName, sal[actorIdx].typeName, sal[actorIdx].topicQos.value,
				null, STATUS_MASK_NONE.value);
		checkHandle(sal[actorIdx].topic, "DomainParticipant.create_topic");
	}

	public void createTopic2(int actorIdx, String topicName) {
		int status = -1;
		participant.get_default_topic_qos(sal[actorIdx].topicQos2);
		sal[actorIdx].topicQos2.value.reliability.kind = ReliabilityQosPolicyKind.RELIABLE_RELIABILITY_QOS;
		sal[actorIdx].topicQos2.value.durability.kind = DurabilityQosPolicyKind.TRANSIENT_DURABILITY_QOS;
		sal[actorIdx].topicQos2.value.history.kind = HistoryQosPolicyKind.KEEP_LAST_HISTORY_QOS;
		sal[actorIdx].topicQos2.value.history.depth = 10000;
		status = participant.set_default_topic_qos(sal[actorIdx].topicQos2.value);
		checkStatus(status,
				"DomainParticipant.set_default_topic_qos");
		System.out.println("=== [createTopic2] : topicName " + topicName + " type = " + sal[actorIdx].typeName2);

		sal[actorIdx].topic2 = participant.create_topic(topicName, sal[actorIdx].typeName2, sal[actorIdx].topicQos2.value,
				null, STATUS_MASK_NONE.value);
		checkHandle(sal[actorIdx].topic2, "DomainParticipant.create_topic");
	}



        public void  createContentFilteredTopic( String topicName, String filter, String[] expr)
	{
	  filteredtopic = participant.create_contentfilteredtopic(topicName,topic, filter, expr);
	  checkHandle(filteredtopic, "DomainParticipant::create_contentfilteredtopic");
	}

        public void  createContentFilteredTopic2( String topicName, String filter, String[] expr)
	{
	  filteredtopic2 = participant.create_contentfilteredtopic(topicName,topic2, filter, expr);
	  checkHandle(filteredtopic2, "DomainParticipant::create_contentfilteredtopic");
	}



        public void  createContentFilteredTopic(int actorIdx, String topicName, String filter, String[] expr)
	{
	  sal[actorIdx].filteredtopic = participant.create_contentfilteredtopic(topicName,sal[actorIdx].topic, filter, expr);
	  checkHandle(sal[actorIdx].filteredtopic, "DomainParticipant::create_contentfilteredtopic");
	}

        public void  createContentFilteredTopic2(int actorIdx,  String topicName, String filter, String[] expr)
	{
	  sal[actorIdx].filteredtopic2 = participant.create_contentfilteredtopic(topicName,sal[actorIdx].topic2, filter, expr);
	  checkHandle(sal[actorIdx].filteredtopic2, "DomainParticipant::create_contentfilteredtopic");
	}



	public void deleteTopics() {
            if (filteredtopic != null) {
		int status = participant.delete_contentfilteredtopic(filteredtopic);
		checkStatus(status, "DDS.DomainParticipant.delete_contentfilteredtopic");
            }
            if (filteredtopic2 != null) {
		int status = participant.delete_contentfilteredtopic(filteredtopic2);
		checkStatus(status, "DDS.DomainParticipant.delete_contentfilteredtopic");
            }
            if (topic != null) {
		int status = participant.delete_topic(topic);
		checkStatus(status, "DDS.DomainParticipant.delete_topic");
            }
            if (topic2 != null) {
		int status = participant.delete_topic(topic2);
		checkStatus(status, "DDS.DomainParticipant.delete_topic");
            }
            for (int i=0;  i<SAL__ACTORS_MAXCOUNT; i++) {
             if (sal[i] != null) {
              if (sal[i].filteredtopic != null) {
  		  int status = participant.delete_contentfilteredtopic(sal[i].filteredtopic);
  		  checkStatus(status, "DDS.DomainParticipant.delete_contentfilteredtopic");
              }
              if (sal[i].filteredtopic2 != null) {
		  int status = participant.delete_contentfilteredtopic(sal[i].filteredtopic2);
		  checkStatus(status, "DDS.DomainParticipant.delete_contentfilteredtopic");
              }
              if (sal[i].topic != null) {
		  int status = participant.delete_topic(sal[i].topic);
		  checkStatus(status, "DDS.DomainParticipant.delete_topic");
              }
              if (sal[i].topic2 != null) {
		  int status = participant.delete_topic(sal[i].topic2);
		  checkStatus(status, "DDS.DomainParticipant.delete_topic");
              }
             }
            }
	}


	public void createPublisher() {
		int status = participant.get_default_publisher_qos(pubQos);
		checkStatus(status,
				"DomainParticipant.get_default_publisher_qos");

		pubQos.value.partition.name = new String[1];
		pubQos.value.partition.name[0] = partitionName;
		publisher = participant.create_publisher(pubQos.value, null,
				STATUS_MASK_NONE.value);
		checkHandle(publisher,
				"DomainParticipant.create_publisher");
	}


	public void createPublisher(int actorIdx) {
		int status = participant.get_default_publisher_qos(sal[actorIdx].pubQos);
		checkStatus(status,
				"DomainParticipant.get_default_publisher_qos");

		sal[actorIdx].pubQos.value.partition.name = new String[1];
		sal[actorIdx].pubQos.value.partition.name[0] = partitionName;
		sal[actorIdx].publisher = participant.create_publisher(sal[actorIdx].pubQos.value, null,
				STATUS_MASK_NONE.value);
		checkHandle(sal[actorIdx].publisher,
				"DomainParticipant.create_publisher");
	}


	public void deletePublisher() {
            if (publisher != null) {
		participant.delete_publisher(publisher);
            }
            for (int i=0;  i<SAL__ACTORS_MAXCOUNT; i++) {
                   if (sal[i] != null) {
                      if (sal[i].publisher != null) {
		         participant.delete_publisher(sal[i].publisher);
                      }
                   }
            }
	}

	public void deleteReaders() {
            if (reader != null) {
		subscriber.delete_datareader(reader);
            }
            if (reader2 != null) {
		subscriber.delete_datareader(reader2);
            }
            for (int i=0;  i<SAL__ACTORS_MAXCOUNT; i++) {
               if (sal[i] != null) {
                 if (sal[i].reader != null) {
	   	   sal[i].subscriber.delete_datareader(sal[i].reader);
                 }
                 if (sal[i].reader2 != null) {
		   sal[i].subscriber.delete_datareader(sal[i].reader2);
                 }
               }
            }
	}

	public void deleteWriters() {
            if (writer != null) {
		publisher.delete_datawriter(writer);
            }
            if (writer2 != null) {
		publisher.delete_datawriter(writer2);
            }
            for (int i=0;  i<SAL__ACTORS_MAXCOUNT; i++) {
               if (sal[i] != null) {
                 if (sal[i].writer != null) {
		   sal[i].publisher.delete_datawriter(sal[i].writer);
                 }
                 if (sal[i].writer2 != null) {
		   sal[i].publisher.delete_datawriter(sal[i].writer2);
                 }
               }
            }
	}



	public void createWriter(boolean autodispose) {
		publisher.get_default_datawriter_qos(WQosH);
		publisher.copy_from_topic_qos(WQosH, topicQos.value);
		WQosH.value.writer_data_lifecycle.autodispose_unregistered_instances = autodispose;
		writer = publisher.create_datawriter(topic, WQosH.value, null,STATUS_MASK_NONE.value);
		checkHandle(writer, "Publisher.create_datawriter");
	}
        
	public void createWriter2(boolean autodispose) {
		publisher.get_default_datawriter_qos(WQosH);
		publisher.copy_from_topic_qos(WQosH, topicQos.value);
		WQosH.value.writer_data_lifecycle.autodispose_unregistered_instances = autodispose;
		writer2 = publisher.create_datawriter(topic2, WQosH.value, null,STATUS_MASK_NONE.value);
		checkHandle(writer2, "Publisher.create_datawriter");
	}


	public void createWriter(int actorIdx, boolean autodispose) {
		sal[actorIdx].publisher.get_default_datawriter_qos(sal[actorIdx].WQosH);
		sal[actorIdx].publisher.copy_from_topic_qos(sal[actorIdx].WQosH, sal[actorIdx].topicQos.value);
		sal[actorIdx].WQosH.value.writer_data_lifecycle.autodispose_unregistered_instances = autodispose;
		sal[actorIdx].writer = sal[actorIdx].publisher.create_datawriter(sal[actorIdx].topic, sal[actorIdx].WQosH.value, null,STATUS_MASK_NONE.value);
		checkHandle(sal[actorIdx].writer, "Publisher.create_datawriter");
		System.out.println("=== [createwriter idx] : topic " + sal[actorIdx].topic + " writer = " + sal[actorIdx].writer);
	}
        
	public void createWriter2(int actorIdx, boolean autodispose) {
		sal[actorIdx].publisher.get_default_datawriter_qos(sal[actorIdx].WQosH);
		sal[actorIdx].publisher.copy_from_topic_qos(sal[actorIdx].WQosH, sal[actorIdx].topicQos2.value);
		sal[actorIdx].WQosH.value.writer_data_lifecycle.autodispose_unregistered_instances = autodispose;
		sal[actorIdx].writer2 = sal[actorIdx].publisher.create_datawriter(sal[actorIdx].topic2, sal[actorIdx].WQosH.value, null,STATUS_MASK_NONE.value);
		checkHandle(sal[actorIdx].writer2, "Publisher.create_datawriter");
		System.out.println("=== [createwriter2 idx] : topic " + sal[actorIdx].topic2 + " writer = " + sal[actorIdx].writer2);
	}



	public void createSubscriber() {
		int status = participant.get_default_subscriber_qos(subQos);
		checkStatus(status,
				"DomainParticipant.get_default_subscriber_qos");

		subQos.value.partition.name = new String[1];
		subQos.value.partition.name[0] = partitionName;
		subscriber = participant.create_subscriber(subQos.value, null,
				STATUS_MASK_NONE.value);
		checkHandle(subscriber,
				"DomainParticipant.create_subscriber");
	}


	public void createSubscriber(int actorIdx) {
		int status = participant.get_default_subscriber_qos(sal[actorIdx].subQos);
		checkStatus(status,
				"DomainParticipant.get_default_subscriber_qos");

		sal[actorIdx].subQos.value.partition.name = new String[1];
		sal[actorIdx].subQos.value.partition.name[0] = partitionName;
		sal[actorIdx].subscriber = participant.create_subscriber(sal[actorIdx].subQos.value, null,
				STATUS_MASK_NONE.value);
		checkHandle(sal[actorIdx].subscriber,
				"DomainParticipant.create_subscriber");
	}



	public void deleteSubscriber() {
                if (subscriber != null) {
  		   participant.delete_subscriber(subscriber);
                }
                for (int i=0;  i<SAL__ACTORS_MAXCOUNT; i++) {
                   if (sal[i] != null) {
                      if (sal[i].subscriber != null) {
		         participant.delete_subscriber(sal[i].subscriber);
                      }
                   }
                }
	}



	public void createReader(boolean filtered) {
	  if (filtered) {
	  	 reader = subscriber.create_datareader(filteredtopic,
		   	 DATAREADER_QOS_USE_TOPIC_QOS.value, null, STATUS_MASK_NONE.value);
	  } else {
		reader = subscriber.create_datareader(topic,
			DATAREADER_QOS_USE_TOPIC_QOS.value, null, STATUS_MASK_NONE.value);
	  }
	  checkHandle(reader, "Subscriber.create_datareader");
	}

	public void createReader2(boolean filtered) {
	  if (filtered) {
	  	 reader2 = subscriber.create_datareader(filteredtopic2,
		   	 DATAREADER_QOS_USE_TOPIC_QOS.value, null, STATUS_MASK_NONE.value);
	  } else {
		reader2 = subscriber.create_datareader(topic2,
			DATAREADER_QOS_USE_TOPIC_QOS.value, null, STATUS_MASK_NONE.value);
	  }
	  checkHandle(reader2, "Subscriber.create_datareader");
	}


	public void createReader(int actorIdx, boolean filtered) {
	  if (filtered) {
	  	 sal[actorIdx].reader = sal[actorIdx].subscriber.create_datareader(sal[actorIdx].filteredtopic,
		   	 DATAREADER_QOS_USE_TOPIC_QOS.value, null, STATUS_MASK_NONE.value);
		System.out.println("=== [createreader idx] : topic " + sal[actorIdx].filteredtopic + " reader = " + sal[actorIdx].reader);
	  } else {
		sal[actorIdx].reader = sal[actorIdx].subscriber.create_datareader(sal[actorIdx].topic,
			DATAREADER_QOS_USE_TOPIC_QOS.value, null, STATUS_MASK_NONE.value);
		System.out.println("=== [createreader idx] : topic " + sal[actorIdx].topic + " reader = " + sal[actorIdx].reader);
	  }
	  checkHandle(sal[actorIdx].reader, "Subscriber.create_datareader");
	  DDS.Duration_t a_timeout = new Duration_t();
	  a_timeout.sec = 5;
	  a_timeout.nanosec = 0;
          sal[actorIdx].sampleAge = 100.0;
	  sal[actorIdx].reader.wait_for_historical_data(a_timeout);
	}

	public void createReader2(int actorIdx,boolean filtered) {
	  if (filtered) {
	   	sal[actorIdx].reader2 = sal[actorIdx].subscriber.create_datareader(sal[actorIdx].filteredtopic2,
		   	 DATAREADER_QOS_USE_TOPIC_QOS.value, null, STATUS_MASK_NONE.value);
		System.out.println("=== [createreader2 idx] : topic " + sal[actorIdx].filteredtopic2 + " reader = " + sal[actorIdx].reader2);
	  } else {
		sal[actorIdx].reader2 = sal[actorIdx].subscriber.create_datareader(sal[actorIdx].topic2,
			DATAREADER_QOS_USE_TOPIC_QOS.value, null, STATUS_MASK_NONE.value);
		System.out.println("=== [createreader2 idx] : topic " + sal[actorIdx].topic2 + " reader = " + sal[actorIdx].reader2);
	  }
	  checkHandle(sal[actorIdx].reader2, "Subscriber.create_datareader");
	  DDS.Duration_t a_timeout = new Duration_t();
	  a_timeout.sec = 5;
	  a_timeout.nanosec = 0;
          sal[actorIdx].sampleAge = 100.0;
	  sal[actorIdx].reader2.wait_for_historical_data(a_timeout);
	}

	public DataReader getReader() {
		return reader;
	}

	public DataReader getReader2() {
		return reader2;
	}

	public DataWriter getWriter() {
		return writer;
	}

	public DataWriter getWriter2() {
		return writer2;
	}

	public Publisher getPublisher() {
		return publisher;
	}

	public Subscriber getSubscriber() {
		return subscriber;
	}

	public Topic getTopic() {
		return topic;
	}

	public Topic getTopic2() {
		return topic2;
	}



	public DataReader getReader(int actorIdx) {
		return sal[actorIdx].reader;
	}

	public DataReader getReader2(int actorIdx) {
		return sal[actorIdx].reader2;
	}

	public DataWriter getWriter(int actorIdx) {
		return sal[actorIdx].writer;
	}

	public DataWriter getWriter2(int actorIdx) {
		return sal[actorIdx].writer2;
	}

	public Publisher getPublisher(int actorIdx) {
		return sal[actorIdx].publisher;
	}

	public Subscriber getSubscriber(int actorIdx) {
		return sal[actorIdx].subscriber;
	}

	public Topic getTopic(int actorIdx) {
		return sal[actorIdx].topic;
	}

	public Topic getTopic2(int actorIdx) {
		return sal[actorIdx].topic2;
	}

	public DomainParticipant getParticipant() {
		return participant;
	}

	public static final int NR_ERROR_CODES = 13;

	/* Array to hold the names for all ReturnCodes. */
	public static String[] RetCodeName = new String[NR_ERROR_CODES];

	static {
		RetCodeName[0] = new String("DDS_RETCODE_OK");
		RetCodeName[1] = new String("DDS_RETCODE_ERROR");
		RetCodeName[2] = new String("DDS_RETCODE_UNSUPPORTED");
		RetCodeName[3] = new String("DDS_RETCODE_BAD_PARAMETER");
		RetCodeName[4] = new String("DDS_RETCODE_PRECONDITION_NOT_MET");
		RetCodeName[5] = new String("DDS_RETCODE_OUT_OF_RESOURCES");
		RetCodeName[6] = new String("DDS_RETCODE_NOT_ENABLED");
		RetCodeName[7] = new String("DDS_RETCODE_IMMUTABLE_POLICY");
		RetCodeName[8] = new String("DDS_RETCODE_INCONSISTENT_POLICY");
		RetCodeName[9] = new String("DDS_RETCODE_ALREADY_DELETED");
		RetCodeName[10] = new String("DDS_RETCODE_TIMEOUT");
		RetCodeName[11] = new String("DDS_RETCODE_NO_DATA");
		RetCodeName[12] = new String("DDS_RETCODE_ILLEGAL_OPERATION");
	}

	/*
	 * Returns the name of an error code.
	 */
	public static String getErrorName(int status) {
		return RetCodeName[status];
	}

	/*
	 * Check the return status for errors. If there is an error, then terminate.
	 */
	public static void checkStatus(int status, String info) {
		if (status != RETCODE_OK.value && status != RETCODE_NO_DATA.value) {
			System.out
					.println("Error in " + info + ": " + getErrorName
(status));
			System.exit(-1);
		}
	}

	/*
	 * Check whether a valid handle has been returned. If not, then terminate.
	 */
	public static void checkHandle(Object handle, String info) {
		if (handle == null) {
			System.out.println("Error in " + info
					+ ": Creation failed: invalid handle");
			System.exit(-1);
		}
	}

}

