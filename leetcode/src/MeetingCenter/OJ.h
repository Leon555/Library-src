#ifndef __OJ_H__
#define __OJ_H__



//CompanyRequest�ṹ�壬����ÿ����˾������ʱ�����ʼ
struct CompanyRequest
{
	int nBegin;
	int nEnd;
};

/* 
�������뺯��
�����
@ret             1����ɹ�, 0����ʧ��
@nCompany        �μ�����Ĺ�˾��
@pCompanyRequest ÿ����˾����ʹ�õ���ֹʱ��
@nCompanyOut     ��ల�Ź�˾�ĸ��������Σ�
@pArrIndex    ���Ź�˾���������飨���Σ�
*/
int ConferenceArrangement(unsigned int nCompany, CompanyRequest* pCompanyRequest, unsigned int* nCompanyOut, unsigned int* pArrIndex);

#endif
