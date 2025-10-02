#include <security/pam_appl.h>
#include <security/pam_ext.h>
#include <security/pam_modules.h>

#include <stdio.h>

PAM_EXTERN int pam_sm_setcred(pam_handle_t *pamh, int flags, int argc,
                              const char **argv) {
  return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc,
                                   const char **argv) {
  pam_info(pamh, "You");
  pam_error(pamh, "Dumbass");

  return PAM_SUCCESS;
}
