#ifndef __OJ_H__
#define __OJ_H__



//CompanyRequest结构体，包含每个公司的申请时间的起始
struct CompanyRequest
{
	int nBegin;
	int nEnd;
};

/* 
会议申请函数
输出：
@ret             1代表成功, 0代表失败
@nCompany        参加申请的公司数
@pCompanyRequest 每个公司请求使用的起止时间
@nCompanyOut     最多安排公司的个数（出参）
@pArrIndex    安排公司的索引数组（出参）
*/
int ConferenceArrangement(unsigned int nCompany, CompanyRequest* pCompanyRequest, unsigned int* nCompanyOut, unsigned int* pArrIndex);

#endif
