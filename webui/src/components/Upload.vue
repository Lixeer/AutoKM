<script setup lang="ts">
import {NUpload, NUploadDragger, NText} from "naive-ui";
</script>

<template>
  <n-upload
      multiple
      directory-dnd
      action=""
      :max="5"
  >
    <n-upload-dragger>
      <div style="margin-bottom: 12px">
      </div>
      <n-text style="font-size: 16px">
        点击或者拖动文件到该区域来上传
      </n-text>
    </n-upload-dragger>
  </n-upload>
</template>

<style scoped>
</style>