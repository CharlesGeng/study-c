(set-background-color "#cce8cf")
(desktop-save-mode 1)
(custom-set-variables
  ;; custom-set-variables was added by Custom.
  ;; If you edit it by hand, you could mess it up, so be careful.
  ;; Your init file should contain only one such instance.
  ;; If there is more than one, they won't work right.
 
'(org-agenda-files nil))
(custom-set-faces
  ;; custom-set-faces was added by Custom.
  ;; If you edit it by hand, you could mess it up, so be careful.
  ;; Your init file should contain only one such instance.
  ;; If there is more than one, they won't work right.
 '(default ((t (:inherit nil :stipple nil :background "#cce8cf" :foreground "#000000" :inverse-video nil :box nil :strike-through nil :overline nil :underline nil :slant normal :weight normal :height 117 :width normal :foundry "unknown" :family "WenQuanYi Micro Hei")))))

(setq default-major-mode 'text-mode)
(add-hook 'text-mode-hook  'turn-on-auto-fill)
(set-fill-column 128)

(global-linum-mode t)
(tool-bar-mode -1)
(menu-bar-mode -1)
