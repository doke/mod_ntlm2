/* mod_ntlm file: $Id: valid.inc.c 44 2006-12-08 01:18:18Z mbaltaks $ */

#include <sys/types.h>
#include <unistd.h>
#include <syslog.h>
#include "smblib-priv.h"
#include "valid.h"

static SMB_Handle_Type SMB_Connect_Server(SMB_Handle_Type, char *, char *);

static int 
Valid_User(char *USERNAME, char *PASSWORD, char *SERVER, char *BACKUP, char *DOMAIN)
{
    char *SMB_Prots[] =
    {"PC NETWORK PROGRAM 1.0",
     "MICROSOFT NETWORKS 1.03",
     "MICROSOFT NETWORKS 3.0",
     "LANMAN1.0",
     "LM1.2X002",
     "Samba",
     "NT LM 0.12",
     "NT LANMAN 1.0",
     NULL};
    SMB_Handle_Type con;

    SMB_Init();
    con = SMB_Connect_Server(NULL, SERVER, DOMAIN);
    if (con == NULL) {          /* Error ... */
        con = SMB_Connect_Server(NULL, BACKUP, DOMAIN);
        if (con == NULL) {
            return (NTV_SERVER_ERROR);
        }
    }
    if (SMB_Negotiate(con, SMB_Prots) < 0) {    /* An error */
        SMB_Discon(con, 0);
        return (NTV_PROTOCOL_ERROR);
    }
    /* Test for a server in share level mode do not authenticate against
     * it */
    if (con->Security == 0) {
        SMB_Discon(con, 0);
        return (NTV_PROTOCOL_ERROR);
    }
    if (SMB_Logon_Server(con, USERNAME, PASSWORD, 0, DOMAIN) < 0) {
        SMB_Discon(con, 0);
        return (NTV_LOGON_ERROR);
    }
    SMB_Discon(con, 0);
    return (NTV_NO_ERROR);
}

static void *
NTLM_Connect(char *SERVER, char *BACKUP, char *DOMAIN, char *nonce)
{
    char *SMB_Prots[] =
    {"PC NETWORK PROGRAM 1.0",
     "MICROSOFT NETWORKS 1.03",
     "MICROSOFT NETWORKS 3.0",
     "LANMAN1.0",
     "LM1.2X002",
     "Samba",
     "NT LM 0.12",
     "NT LANMAN 1.0",
     NULL};
    SMB_Handle_Type con;

    SMB_Init();
    con = SMB_Connect_Server(NULL, SERVER, DOMAIN);
    if (con == NULL) {          /* Error ... */
        con = SMB_Connect_Server(NULL, BACKUP, DOMAIN);
        if (con == NULL) {
            return (NULL);
        }
    }
    if (SMB_Negotiate(con, SMB_Prots) < 0) {    /* An error */
        SMB_Discon(con, 0);
        return (NULL);
    }
    /* Test for a server in share level mode do not authenticate
     * against it */
    if (con->Security == 0) {
        SMB_Discon(con, 0);
        return (NULL);
    }
    memcpy(nonce, con->Encrypt_Key, 8);

    return con;
}

static int 
NTLM_Auth(void *handle, char *USERNAME, char *PASSWORD, int flag, char *DOMAIN)
{
    SMB_Handle_Type con = handle;

    if (SMB_Logon_Server(con, USERNAME, PASSWORD, flag, DOMAIN) < 0) {
        return (NTV_LOGON_ERROR);
    }
    return NTV_NO_ERROR;
}

static void 
NTLM_Disconnect(void *handle)
{
    SMB_Handle_Type con = handle;
    SMB_Discon(con, 0);
}
