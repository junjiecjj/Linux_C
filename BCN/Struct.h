#ifndef _STRUCT_CJJ
#define _STRUCT_CJJ

typedef unsigned long ULONG;

typedef unsigned char UCHAR;

#ifndef BOOL_TYPEDEFINE
#define BOOL_TYPEDEFINE
typedef enum {FALSE = 0, TRUE = 1}BOOL;
#endif

enum
{
	ENUM_SCAN_RESET= 0,
	ENUM_SCAN_SCAN = 1,
	ENUM_SCAN_POINT = 2,
	ENUM_SCAN_TRACK = 3,
	ENUM_SCAN_ZERO_POINT = 4,
	ENUM_SCAN_OPEN_POINT= 5,
	ENUM_SCAN_RECORD_POINT = 6,
	ENUM_SCAN_MEAR_POINT = 7,
	ENUM_SCAN_XYZFILTER_POINT = 8,
	ENUM_SCAN_SMOOTH_POINT = 9,
	ENUM_SCAN_OPEN_POINT_MOVE = 10
};

typedef struct TAP_HJ_ABTION_BAND_DATA_MSG
{
	unsigned short TimeStampL;
	unsigned char LockFlag;
	unsigned char FrameStart;
	unsigned short TimeStampH;
	unsigned short TimeStampM;

#if 0
	unsigned short  UAZ1:1;
	unsigned short  UAZ:15;
	unsigned short  Uel1:1;
	unsigned short  Uel:15;
#endif
	short  Uel;
	short  UAZ;

	unsigned char AGCH;
	unsigned short AGCL;
	char SNR;
} TAP_HJ_ABTION_BAND_DATA_MSG;

typedef struct TAP_HJ_GET_FM_FPGA_DATA_MSG
{
	unsigned long long len;

	unsigned int   FrameStart1;  // 帧头
	unsigned short FrameStart2;  // 帧头
	unsigned short FrameStart3;  // 帧头

	unsigned int	Second		:6;		//秒
	unsigned int	Minute		:6;		//分钟
	unsigned int	Hour		:6;		//小时
	unsigned int	Day			:10;	//天
	unsigned int	Bak			:4;		//保留位
	unsigned int 	uSecond;			//微秒

	unsigned long long reserve1;

	unsigned long long LRFlag;

	unsigned short BeamNo14;
	unsigned short BeamNo13;
	unsigned short BeamNo12;
	unsigned short BeamNo11;
	// unsigned long long BeamNo1;
	// unsigned long long BeamNo2;
	unsigned short BeamNo24;
	unsigned short BeamNo23;
	unsigned short BeamNo22;
	unsigned short BeamNo21;
	unsigned long long AMP1;
	unsigned long long AMP2;
	unsigned long long AMP3;
	unsigned long long AMP4;
	unsigned long long AMP5;
	unsigned long long AMP6;
	unsigned long long AMP7;
	unsigned long long AMP8;
	unsigned long long FFT1;
	unsigned long long FFT2;
	unsigned long long FFT3;
	unsigned long long FFT4;
	unsigned long long FFT5;
	unsigned long long FFT6;
	unsigned long long FFT7;
	unsigned long long FFT8;
	unsigned long long reserve2;
	unsigned long long reserve3;
} TAP_HJ_GET_FM_FPGA_DATA_MSG;

typedef struct TAP_HJ_GET_SM_FPGA_DATA_MSG
{
	unsigned long long len;

	unsigned int FrameStart1;  // 帧头
	unsigned short FrameStart2;  // 帧头
	unsigned short FrameStart3;  // 帧头

	unsigned int	Second		:6;		//秒
	unsigned int	Minute		:6;		//分钟
	unsigned int	Hour		:6;		//小时
	unsigned int	Day			:10;	//天
	unsigned int	Bak			:4;		//保留位
	unsigned int 	uSecond;			//微秒

	unsigned long long reserve1;
	unsigned long long LRFlag;

	unsigned short BeamNo11;
	unsigned short BeamNo12;
	unsigned short BeamNo13;
	unsigned short BeamNo14;
	// unsigned long long BeamNo1;
	// unsigned long long BeamNo2;
	unsigned short BeamNo21;
	unsigned short BeamNo22;
	unsigned short BeamNo23;
	unsigned short BeamNo24;

	unsigned long long AMP1;
	unsigned long long AMP2;
	unsigned long long AMP3;
	unsigned long long AMP4;
	unsigned long long AMP5;
	unsigned long long AMP6;
	unsigned long long AMP7;
	unsigned long long AMP8;
	unsigned long long FFT1;
	unsigned long long FFT2;
	unsigned long long FFT3;
	unsigned long long FFT4;
	unsigned long long FFT5;
	unsigned long long FFT6;
	unsigned long long FFT7;
	unsigned long long FFT8;

	unsigned short JCIndex1;
	unsigned short JCIndex2;
	unsigned short JCIndex3;
	unsigned short JCIndex4;

	unsigned short JCIndex5;
	unsigned short JCIndex6;
	unsigned short JCIndex7;
	unsigned short JCIndex8;
} TAP_HJ_GET_SM_FPGA_DATA_MSG;

// DBF发给BCN的和差结构体
typedef struct TAP_HJ_GET_SUMDIFF_FPGA_DATA_MSG
{
	unsigned long long len;
	unsigned int FrameStart1;
	unsigned short FrameStart2;
	unsigned short FrameStart3;

	//	unsigned long long GPSTime;

	unsigned int	Second		:6;
	unsigned int	Minute		:6;
	unsigned int	Hour		:6;
	unsigned int	Day			:10;
	unsigned int	Bak			:4;
	unsigned int 	uSecond;			//微秒

	unsigned long long reserve1;

	long long leftSum;
	long long reserve2;
	long long leftAzI;
	long long leftAzQ;
	long long leftEleI;
	long long leftEleQ;

	long long rightSum;
	long long reserve3;
	long long rightAzI;
	long long rightAzQ;
	long long rightEleI;
	long long rightEleQ;

	long long reserve4[6];
} TAP_HJ_GET_SUMDIFF_FPGA_DATA_MSG;

// DBF发给BCN的9波束结构体
typedef struct TAP_HJ_GET_SUMAMP_FPGA_DATA_MSG
{
	unsigned long long len;

	unsigned int FrameStart1;
	unsigned short FrameStart2;  // 帧头
	unsigned short FrameStart3;  // 帧头

	// unsigned long long GPSTime;
	unsigned int	Second		:6;		//秒
	unsigned int	Minute		:6;		//分钟
	unsigned int	Hour		:6;		//小时
	unsigned int	Day			:10;	//天
	unsigned int	Bak			:4;		//保留位
	unsigned int 	uSecond;			//微秒

	unsigned long long reserve1;
	unsigned long long leftX1;
	unsigned long long leftX2;
	unsigned long long leftX3;
	unsigned long long leftX4;
	unsigned long long leftX5;
	unsigned long long leftX6;
	unsigned long long leftX7;
	unsigned long long leftX8;
	unsigned long long leftX9;
	unsigned long long rightX1;
	unsigned long long rightX2;
	unsigned long long rightX3;
	unsigned long long rightX4;
	unsigned long long rightX5;
	unsigned long long rightX6;
	unsigned long long rightX7;
	unsigned long long rightX8;
	unsigned long long rightX9;
} TAP_HJ_GET_SUMAMP_FPGA_DATA_MSG;

typedef struct TAP_ABTION_RAPIDIO_DATA_MSG
{
	unsigned char			       		ucDDCid;
	TAP_HJ_ABTION_BAND_DATA_MSG    		pBandReMsg;
	TAP_HJ_GET_FM_FPGA_DATA_MSG    		pDBFFMMsg;
	TAP_HJ_GET_SM_FPGA_DATA_MSG    		pDBFSMMsg;
	TAP_HJ_GET_SUMDIFF_FPGA_DATA_MSG 	pDBFSDMsg;
	TAP_HJ_GET_SUMAMP_FPGA_DATA_MSG 	pDBFSAMsg;
} TAP_ABTION_RAPIDIO_DATA_MSG;


typedef struct DirectionPLOTIQ
{
    struct                      DirectionPLOTIQ* Prev;
    struct                      DirectionPLOTIQ* Next;
    unsigned char           ucDDCid;
	TAP_HJ_ABTION_BAND_DATA_MSG       pBandReMsg;
 	TAP_HJ_GET_FM_FPGA_DATA_MSG       pDBFFMMsg;
 	TAP_HJ_GET_SM_FPGA_DATA_MSG       pDBFSMMsg;
 	TAP_HJ_GET_SUMDIFF_FPGA_DATA_MSG  pDBFSDMsg;
 	TAP_HJ_GET_SUMAMP_FPGA_DATA_MSG   pDBFSAMsg;
}DirectionPLOTIQ;

typedef struct TAP_HJSYS_PARM_MANAGE
{
	unsigned int		TaskMask;
	char				mid[10];
	unsigned char		FlatState;
	unsigned char		capture;
	unsigned char		RRFFreq1Flag;
	unsigned char		RRFFreq2Flag;
	unsigned char		CurWorkType;
	unsigned char		CurWorkTypeLast;
	unsigned char		TaskStaus;
	unsigned char		sendDataType;
	unsigned char		SendDataState;
	unsigned char		AngleSaveState;

	unsigned char		OrbitPredictStatus;
	unsigned char		DigitalLeadStatus;
	unsigned char		MultiBeamStatus;
	unsigned char		FMAngleErrStatus;
	unsigned char		SSMeaErrStatus;
	unsigned char		SSTeleErrStatus;

    unsigned char		IMU1Flag;
    unsigned char		IMU2Flag;

	ULONG		MultiBeamTime;
	ULONG		FMAngleErrTime;
	ULONG		SSMeaErrTime;
	ULONG		SSTeleErrTime;

	unsigned long		AngleEffective;


	int                     DigleadAzi;
	int                     DigleadElev;
	int                     MultiBeamAzi;
	int                     MultiBeamElev;
	int                     TraLeadAzi;
	int                     TraLeadElev;

	double                     fFMAziErrVol;
	double                     fFMElevErrVol;
	double                     fSSMeaAziErrVol;
	double                     fSSMeaElevErrVol;
	double                     fSSTeleAziErrVol;
	double                     fSSTeleElevErrVol;

	double		fFMAGCVol;
	double		fSSMeaAGCVol;
	double		fSSTeleAGCVol;
	double		fFMSNRVol;
	double		fSSMeaSNRVol;
	double		fSSTeleSNRVol;

	unsigned int            T0Day;
	unsigned int            T0Time;
	double					T0mjday;
	BOOL					bT0flag;//应急写入起飞时

	unsigned char		CPUUse;
	unsigned char		RAMUse;
	unsigned long		upFreq;
	unsigned long		downFreq;
	unsigned char		bf1;
	unsigned char		bf2;
	unsigned long		f1;
	unsigned long		f2;
	unsigned char		captureTimeTH;// time 1--10s
	unsigned char		AngleProcFlag;
	unsigned short		reportCyc;

	char				FilterInitT;
	char				FilterInitNum;
	unsigned int		Reserve[4]; //

	double				longitude;
	double				lat;
	double				high;
	double 			    yaw; //hangxiang
	double   			roll; //fangun
	double   			pitch; //fuyang  //站址坐标装订
	unsigned char		ZenithPassStatus;

	double				VE;
	double				VN;
	double				VH;
	double				Xpos;  // 上帧的位置
	double				Ypos;
	double				Zpos;
	unsigned char		AimFlag;
	double				Xwait;
	double				Ywait;
	double				Zwait;
	float					startElev;
	float					stopElev;
	unsigned int       Date;
	float       Time;

	unsigned char				Select1;
	unsigned char				Select2;
	unsigned char               Select3;
	unsigned char               MemoryTrackTime;

	unsigned short      A1;
	unsigned short      E1;
	unsigned short      A2;
	unsigned short      E2;
	unsigned short      SBF;

	//add process
    unsigned char		CurWorkTypeR;
    unsigned char		TaskStausBH;
    ULONG				digitDataTime;
    // pro
    unsigned char 		ucDDCid;

    float    	AziZero;
    float   	ElevZero;//角度零值装订

    unsigned char		AngleOffsetFlag;
    float   			ferrAzi;
    float   			ferrEle;
    int   				errTime;

    float				 	MaxOutLevelAngle;
    float   				MaxOutLevelAzi;
    float   				Sb;
    float					Cs;
    float   				Ce;
    float   				Eg;

    unsigned short    		C_A;
    unsigned short    		C_E;
    // status
	int                 CurAzi;
	int                 CurElev;
	int                 CmdAzi;
	int                 CmdElev;
	int                 StationAzi;
	int                 StationElev;

	//数引数据
	double					X;
	double					Y;
	double					Z;
	double					VX;
	double					VY;
	double					VZ;
	double 					mjday;

    double	BANDR;
    ULONG	BANDRTime;
    BOOL	bBandFlag;

    double	SR;
    ULONG	SRTime;
    BOOL	SRFlag;

    double	CR;
    ULONG	CRTime;
    BOOL	CRFlag;

	BOOL	bTrackReport;

	long   f0;
	double beam_fai;
	double beam_seta;

    // ACU
	int					nAcuFirst;
    double				ACU_Azloc;
    double				ACU_Eleloc;
    double				ACU_AzEcef;
    double				ACU_EleEcef;
    unsigned char		bACU_First;
    double				ACU_AzEceft;
    double				ACU_EleEceft;

    double				ACU_REcef;
    double				LLTV_AzEcef;
    double				LLTV_EleEcef;

    // LLTV
    short			MissAzi;
    short			MissElev;
    int				StarPosAzi;
    int				StarPosElev;

    //
	int                 FMAzi;
	int                 FMElev;
	int                 SSMeaAzi;
	int                 SSMeaElev;
	int                 SSTeleAzi;
	int                 SSTeleElev;

	int                 CheckAzi;
	int                 CheckElev;
	int                 SumDiffAzi;
	int                 SumDiffElev;

	// add angle
	ULONG				AngleEffectiveTime;
	int                 ProgramAziM;
	int                 ProgramElevM;
	int                 ProgramAzi;
	int                 ProgramElev;

	int                 DigleadAziM;
	int                 DigleadElevM;

	unsigned char		TZLeadStatus;
	int                 TZleadAzi;
	int                 TZleadElev;
	int                 TZleadAziM;
	int                 TZleadElevM;

	int                 RealTGroundAzi;
	int                 RealTGroundElev;
	int                 RealTMeasureAzi;
	int                 RealTMeasureElev;

	double              dElecBeamAzi;
	double              dElecBeamElev;
    unsigned char		TrackScanFirst;
    unsigned char		scanfFirst;
    unsigned char		SureFirst;


    unsigned int		BeamNum;
    unsigned int		ScanNum;
    unsigned int		ScanMood;
    unsigned char		ScanMoodReport;
    unsigned int		ScanInterbal;
    unsigned int		captureInter;
    double				bpAz[65];
    double				bpEle[65];

}TAP_HJSYS_PARM_MANAGE;

/*点迹信息*/
typedef struct PLOT_BASE_INFO_CO
{
    ULONG        dSystemTime;                           /*! 时间 */
    double       dRange;                                /*! 距离 */
    double	     dAzimuth;                              /*! 方位 */
    double	     dElevation;                            /*! 俯仰 */
	double	     xlocal;                                /*! x方向余弦 */
	double	     zlocal;                           	   /*! z方向余弦 */
    double		 dAmp; 								   // 目标幅度
    double       dsore;								   // 目标质量
    UCHAR		 circle;								   // 圈数
    UCHAR		 bp; 								   // 模拟波位号
    UCHAR		 sbp; 								   // 数字波位号
}PLOT_BASE_INFO_CO;

/*!  相关点迹信息 */
typedef struct PLOT_MANAGE_CO
{
	BOOL         bUsedFlag;                              /*!< 是否已经在使用标志*/
    ULONG        dSystemTime;                           /*! 时间 */
    unsigned short    Frame;                            /*!  更新帧数 */
    PLOT_BASE_INFO_CO plot[5];
}PLOT_MANAGE_CO;

typedef struct STRUCT1
{
    int a ;
    double b;
    float c;
    unsigned char d;
    int e;
    int f;
} STR1;


typedef struct STRUCT2
{
    int a ;
    double b;
    float c;
    unsigned char d;
    //int e;
    //int f;
} STR2;


#endif // _STRUCT_CJJ

