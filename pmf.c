#include <security/pam_appl.h>
#include <security/pam_ext.h>
#include <security/pam_modules.h>

#include <inttypes.h>
#include <stdlib.h>

#include <arpa/inet.h>

#include <openssl/rand.h>

#include "tpr.h"

PAM_EXTERN int pam_sm_setcred(pam_handle_t *pamh, int flags, int argc,
                              const char **argv) {
  return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc,
                                   const char **argv) {
  const struct pam_conv *conv = NULL;
  struct pam_message msg = {0};
  const struct pam_message *msgp = &msg;
  struct pam_response *resp = NULL;

  tpr_clg_t clg = tpr_mk_clg();
  pam_info(pamh, "%s", tpr_str_clg(clg));

  if (pam_get_item(pamh, PAM_CONV, (const void **)&conv) != PAM_SUCCESS) {
    pam_error(pamh, "PAM Auth failure, failed to get conversation");
    return PAM_CONV_ERR;
  }

  msg.msg = "Enter FC: ";
  msg.msg_style = PAM_PROMPT_ECHO_OFF;

  if (conv->conv(1, &msgp, &resp, conv->appdata_ptr) != PAM_SUCCESS || !resp ||
      !resp->resp) {
    if (resp)
      free(resp);
    pam_error(pamh, "PAM Auth failure, failed to get FC");
    return PAM_CONV_ERR;
  }

  pam_info(pamh, "'%s'", resp->resp);

  return PAM_SUCCESS;
}
