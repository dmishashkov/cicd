#!/bin/bash
BOT_TOKEN="6737462128:AAHtcor9FXs24gYOg_3eJPueSe8r39kDqv8"
TELEGRAM_USER_ID="494370671"

URL="https://api.telegram.org/bot$BOT_TOKEN/sendMessage"
TIME="5"

TEXT="Deploy status: $1%0A%0AProject:+$CI_PROJECT_NAME%0AURL:+$CI_PROJECT_URL/pipelines/$CI_PIPELINE_ID/%0ABranch:+$CI_COMMIT_REF_SLUG"
# TEXT="FSDF"

curl -s --max-time $TIME -d "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null