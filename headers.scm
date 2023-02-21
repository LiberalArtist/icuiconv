(use-modules
 (gnu packages base)
 (gnu packages musl)
 (guix gexp)
 (guix git-download)
 (guix packages)
 (guix download)
 (guix build-system copy)
 ((guix licenses) #:prefix license:))

(define-public freebsd
  (package
    (name "freebsd")
    (version "13.1.0")
    (source (origin
              (method git-fetch)
              (uri (git-reference
                    (url "https://git.FreeBSD.org/src.git")
                    (commit (string-append "release/" version))))
              (sha256
               (base32
                "14nhk0kls83xfb64d5xy14vpi6k8laswjycjg80indq9pkcr2rlv"))
              (file-name (git-file-name name version))))
    (build-system copy-build-system)
    (arguments
     (list
      #:install-plan #~`(("include/iconv.h" "include/"))))
    (home-page "https://FreeBSD.org")
    (synopsis "TODO")
    (description
     "TODO")
    (license #f))) ;which bsd?
               

(define-public apr-iconv
  (package
    (name "apr-iconv")
    (version "1.2.2")
    (source (origin
              (method url-fetch)
              (uri (string-append "mirror://apache/apr/apr-iconv-"
                                  version ".tar.bz2"))
             (sha256
              (base32
               "04skqdvh7jbkr53kj7i9symnml9rb1skn3h0f7v8a8rgwc7lwibx"))))
    (build-system copy-build-system)
    (arguments
     (list
      #:install-plan #~`(("include/apr_iconv.h" "include/"))))
    (home-page "https://apr.apache.org/")
    (synopsis "TODO")
    (description
     "TODO")
    (license license:asl2.0))) ;; <- check

(define-public headers
  (file-union "include"
              `(("libiconv/iconv.h"
                 ,(file-append libiconv "/include/iconv.h"))
                ("glibc/iconv.h"
                 ,(file-append glibc "/include/iconv.h"))
                ("freebsd/iconv.h"
                 ,(file-append freebsd "/include/iconv.h"))
                ("musl/iconv.h"
                 ,(file-append musl "/include/iconv.h"))
                ("apr_iconv.h"
                 ,(file-append apr-iconv "/include/apr_iconv.h")))))

headers
