/*
 * File:	mcf5xxx_vectors.s
 * Purpose:	ColdFire vector table
 */
	.global VECTOR_TABLE
	.global _VECTOR_TABLE
	
	.extern __SP_INIT
	.extern _asm_startmeup
	.extern asm_exception_handler
	.extern _ISR_FrameHandler

	.text


/*
 * Exception Vector Table
 */
VECTOR_TABLE:
_VECTOR_TABLE:
INITSP:		.long	__SP_INIT				/* Initial SP			*/
INITPC:		.long	_asm_startmeup			/* Initial PC			*/
vector002:	.long	asm_exception_handler	/* Access Error			*/
vector003:	.long	asm_exception_handler	/* Address Error		*/
vector004:	.long	asm_exception_handler	/* Illegal Instruction	*/
vector005:	.long	asm_exception_handler	/* Reserved				*/
vector006:	.long	asm_exception_handler	/* Reserved				*/
vector007:	.long	asm_exception_handler	/* Reserved				*/
vector008:	.long	asm_exception_handler	/* Privilege Violation	*/
vector009:	.long	asm_exception_handler	/* Trace				*/
vector010:	.long	asm_exception_handler	/* Unimplemented A-Line	*/
vector011:	.long	asm_exception_handler	/* Unimplemented F-Line	*/
vector012:	.long	asm_exception_handler	/* Debug Interrupt		*/
vector013:	.long	asm_exception_handler	/* Reserved				*/
vector014:	.long	asm_exception_handler	/* Format Error			*/
vector015:	.long	asm_exception_handler	/* Unitialized Int.		*/
vector016:	.long	asm_exception_handler	/* Reserved				*/
vector017:	.long	asm_exception_handler	/* Reserved				*/
vector018:	.long	asm_exception_handler	/* Reserved				*/
vector019:	.long	asm_exception_handler	/* Reserved				*/
vector020:	.long	asm_exception_handler	/* Reserved				*/
vector021:	.long	asm_exception_handler	/* Reserved				*/
vector022:	.long	asm_exception_handler	/* Reserved				*/
vector023:	.long	asm_exception_handler	/* Reserved				*/
vector024:	.long	asm_exception_handler	/* Spurious Interrupt	*/
vector025:	.long	asm_exception_handler	/* Autovector Level 1	*/
vector026:	.long	asm_exception_handler	/* Autovector Level 2	*/
vector027:	.long	asm_exception_handler	/* Autovector Level 3	*/
vector028:	.long	asm_exception_handler	/* Autovector Level 4	*/
vector029:	.long	asm_exception_handler	/* Autovector Level 5	*/
vector030:	.long	asm_exception_handler	/* Autovector Level 6	*/
vector031:	.long	asm_exception_handler	/* Autovector Level 7	*/
vector032:	.long	asm_exception_handler	/* TRAP #0				*/
vector033:	.long	asm_exception_handler	/* TRAP #1				*/
vector034:	.long	asm_exception_handler	/* TRAP #2				*/
vector035:	.long	asm_exception_handler	/* TRAP #3				*/
vector036:	.long	asm_exception_handler	/* TRAP #4				*/
vector037:	.long	asm_exception_handler	/* TRAP #5				*/
vector038:	.long	asm_exception_handler	/* TRAP #6				*/
vector039:	.long	asm_exception_handler	/* TRAP #7				*/
vector040:	.long	asm_exception_handler	/* TRAP #8				*/
vector041:	.long	asm_exception_handler	/* TRAP #9				*/
vector042:	.long	asm_exception_handler	/* TRAP #10				*/
vector043:	.long	asm_exception_handler	/* TRAP #11				*/
vector044:	.long	asm_exception_handler	/* TRAP #12				*/
vector045:	.long	asm_exception_handler	/* TRAP #13				*/
vector046:	.long	asm_exception_handler	/* TRAP #14				*/
vector047:	.long	asm_exception_handler	/* TRAP #15				*/
vector048:	.long	asm_exception_handler	/* Reserved				*/
vector049:	.long	asm_exception_handler	/* Reserved				*/
vector050:	.long	asm_exception_handler	/* Reserved				*/
vector051:	.long	asm_exception_handler	/* Reserved				*/
vector052:	.long	asm_exception_handler	/* Reserved				*/
vector053:	.long	asm_exception_handler	/* Reserved				*/
vector054:	.long	asm_exception_handler	/* Reserved				*/
vector055:	.long	asm_exception_handler	/* Reserved				*/
vector056:	.long	asm_exception_handler	/* Reserved				*/
vector057:	.long	asm_exception_handler	/* Reserved				*/
vector058:	.long	asm_exception_handler	/* Reserved				*/
vector059:	.long	asm_exception_handler	/* Reserved				*/
vector060:	.long	asm_exception_handler	/* Reserved				*/
vector061:	.long	asm_exception_handler	/* Reserved				*/
vector062:	.long	asm_exception_handler	/* Reserved				*/
vector063:	.long	asm_exception_handler	/* Reserved				*/
vector064:	.long	asm_exception_handler
vector065:	.long	asm_exception_handler
vector066:	.long	asm_exception_handler
vector067:	.long	asm_exception_handler
vector068:	.long	_ISR_FrameHandler
vector069:	.long	asm_exception_handler
vector070:	.long	asm_exception_handler
vector071:	.long	asm_exception_handler
vector072:	.long	asm_exception_handler
vector073:	.long	asm_exception_handler
vector074:	.long	asm_exception_handler
vector075:	.long	asm_exception_handler
vector076:	.long	asm_exception_handler
vector077:	.long	asm_exception_handler
vector078:	.long	asm_exception_handler
vector079:	.long	asm_exception_handler
vector080:	.long	asm_exception_handler
vector081:	.long	asm_exception_handler
vector082:	.long	asm_exception_handler
vector083:	.long	asm_exception_handler
vector084:	.long	asm_exception_handler
vector085:	.long	asm_exception_handler
vector086:	.long	asm_exception_handler
vector087:	.long	asm_exception_handler
vector088:	.long	asm_exception_handler
vector089:	.long	asm_exception_handler
vector090:	.long	asm_exception_handler
vector091:	.long	asm_exception_handler
vector092:	.long	asm_exception_handler
vector093:	.long	asm_exception_handler
vector094:	.long	asm_exception_handler
vector095:	.long	asm_exception_handler
vector096:	.long	asm_exception_handler
vector097:	.long	asm_exception_handler
vector098:	.long	asm_exception_handler
vector099:	.long	asm_exception_handler
vector100:	.long	asm_exception_handler
vector101:	.long	asm_exception_handler
vector102:	.long	asm_exception_handler
vector103:	.long	asm_exception_handler
vector104:	.long	asm_exception_handler
vector105:	.long	asm_exception_handler
vector106:	.long	asm_exception_handler
vector107:	.long	asm_exception_handler
vector108:	.long	asm_exception_handler
vector109:	.long	asm_exception_handler
vector110:	.long	asm_exception_handler
vector111:	.long	asm_exception_handler
vector112:	.long	asm_exception_handler
vector113:	.long	asm_exception_handler
vector114:	.long	asm_exception_handler
vector115:	.long	asm_exception_handler
vector116:	.long	asm_exception_handler
vector117:	.long	asm_exception_handler
vector118:	.long	asm_exception_handler
vector119:	.long	asm_exception_handler
vector120:	.long	asm_exception_handler
vector121:	.long	asm_exception_handler
vector122:	.long	asm_exception_handler
vector123:	.long	asm_exception_handler
vector124:	.long	asm_exception_handler
vector125:	.long	asm_exception_handler
vector126:	.long	asm_exception_handler
vector127:	.long	asm_exception_handler
vector128:	.long	asm_exception_handler
vector129:	.long	asm_exception_handler
vector130:	.long	asm_exception_handler
vector131:	.long	asm_exception_handler
vector132:	.long	asm_exception_handler
vector133:	.long	asm_exception_handler
vector134:	.long	asm_exception_handler
vector135:	.long	asm_exception_handler
vector136:	.long	asm_exception_handler
vector137:	.long	asm_exception_handler
vector138:	.long	asm_exception_handler
vector139:	.long	asm_exception_handler
vector140:	.long	asm_exception_handler
vector141:	.long	asm_exception_handler
vector142:	.long	asm_exception_handler
vector143:	.long	asm_exception_handler
vector144:	.long	asm_exception_handler
vector145:	.long	asm_exception_handler
vector146:	.long	asm_exception_handler
vector147:	.long	asm_exception_handler
vector148:	.long	asm_exception_handler
vector149:	.long	asm_exception_handler
vector150:	.long	asm_exception_handler
vector151:	.long	asm_exception_handler
vector152:	.long	asm_exception_handler
vector153:	.long	asm_exception_handler
vector154:	.long	asm_exception_handler
vector155:	.long	asm_exception_handler
vector156:	.long	asm_exception_handler
vector157:	.long	asm_exception_handler
vector158:	.long	asm_exception_handler
vector159:	.long	asm_exception_handler
vector160:	.long	asm_exception_handler
vector161:	.long	asm_exception_handler
vector162:	.long	asm_exception_handler
vector163:	.long	asm_exception_handler
vector164:	.long	asm_exception_handler
vector165:	.long	asm_exception_handler
vector166:	.long	asm_exception_handler
vector167:	.long	asm_exception_handler
vector168:	.long	asm_exception_handler
vector169:	.long	asm_exception_handler
vector170:	.long	asm_exception_handler
vector171:	.long	asm_exception_handler
vector172:	.long	asm_exception_handler
vector173:	.long	asm_exception_handler
vector174:	.long	asm_exception_handler
vector175:	.long	asm_exception_handler
vector176:	.long	asm_exception_handler
vector177:	.long	asm_exception_handler
vector178:	.long	asm_exception_handler
vector179:	.long	asm_exception_handler
vector180:	.long	asm_exception_handler
vector181:	.long	asm_exception_handler
vector182:	.long	asm_exception_handler
vector183:	.long	asm_exception_handler
vector184:	.long	asm_exception_handler
vector185:	.long	asm_exception_handler
vector186:	.long	asm_exception_handler
vector187:	.long	asm_exception_handler
vector188:	.long	asm_exception_handler
vector189:	.long	asm_exception_handler
vector190:	.long	asm_exception_handler
vector191:	.long	asm_exception_handler
vector192:	.long	asm_exception_handler
vector193:	.long	asm_exception_handler
vector194:	.long	asm_exception_handler
vector195:	.long	asm_exception_handler
vector196:	.long	asm_exception_handler
vector197:	.long	asm_exception_handler
vector198:	.long	asm_exception_handler
vector199:	.long	asm_exception_handler
vector200:	.long	asm_exception_handler
vector201:	.long	asm_exception_handler
vector202:	.long	asm_exception_handler
vector203:	.long	asm_exception_handler
vector204:	.long	asm_exception_handler
vector205:	.long	asm_exception_handler
vector206:	.long	asm_exception_handler
vector207:	.long	asm_exception_handler
vector208:	.long	asm_exception_handler
vector209:	.long	asm_exception_handler
vector210:	.long	asm_exception_handler
vector211:	.long	asm_exception_handler
vector212:	.long	asm_exception_handler
vector213:	.long	asm_exception_handler
vector214:	.long	asm_exception_handler
vector215:	.long	asm_exception_handler
vector216:	.long	asm_exception_handler
vector217:	.long	asm_exception_handler
vector218:	.long	asm_exception_handler
vector219:	.long	asm_exception_handler
vector220:	.long	asm_exception_handler
vector221:	.long	asm_exception_handler
vector222:	.long	asm_exception_handler
vector223:	.long	asm_exception_handler
vector224:	.long	asm_exception_handler
vector225:	.long	asm_exception_handler
vector226:	.long	asm_exception_handler
vector227:	.long	asm_exception_handler
vector228:	.long	asm_exception_handler
vector229:	.long	asm_exception_handler
vector230:	.long	asm_exception_handler
vector231:	.long	asm_exception_handler
vector232:	.long	asm_exception_handler
vector233:	.long	asm_exception_handler
vector234:	.long	asm_exception_handler
vector235:	.long	asm_exception_handler
vector236:	.long	asm_exception_handler
vector237:	.long	asm_exception_handler
vector238:	.long	asm_exception_handler
vector239:	.long	asm_exception_handler
vector240:	.long	asm_exception_handler
vector241:	.long	asm_exception_handler
vector242:	.long	asm_exception_handler
vector243:	.long	asm_exception_handler
vector244:	.long	asm_exception_handler
vector245:	.long	asm_exception_handler
vector246:	.long	asm_exception_handler
vector247:	.long	asm_exception_handler
vector248:	.long	asm_exception_handler
vector249:	.long	asm_exception_handler
vector250:	.long	asm_exception_handler
vector251:	.long	asm_exception_handler
vector252:	.long	asm_exception_handler
vector253:	.long	asm_exception_handler
vector254:	.long	asm_exception_handler
vector255:	.long	asm_exception_handler
					
CFM_FLASH_CONFIG:
_CFM_FLASH_CONFIG: 
/* 
 * CFM Flash Configuration Field 
 */
KEY_UPPER:  .long   0x00000000
KEY_LOWER:  .long   0x00000000
CFMPROT:    .long   0x00000000
CFMSACC:    .long   0x00000000
CFMDACC:    .long   0x00000000
CFMSEC:     .long   0x00000000

	
	.end
