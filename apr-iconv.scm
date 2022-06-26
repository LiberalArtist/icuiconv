(use-modules (gnu packages apr)
             (guix packages)
             (guix download)
             (guix build-system gnu)
             ((guix licenses)
              #:prefix l:))

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
    (build-system gnu-build-system)
    (inputs
     (list apr))
    (home-page "https://apr.apache.org/")
    (synopsis "TODO")
    (description
     "TODO")
    (license l:asl2.0)))
apr-iconv
