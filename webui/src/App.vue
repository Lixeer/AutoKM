<script setup lang="ts">
import {NTabs, NTabPane, NCard} from "naive-ui";
import State from "@/components/State.vue";
import Edit from "@/components/Edit.vue";
import Upload from "@/components/Upload.vue";
import Introduction from "@/components/Introduction.vue";
</script>

<template>
  <n-card :bordered="false" class="app">
    <template #header>
      <h1 class="logo">
        AutoKM
      </h1>
    </template>
    <n-tabs type="line" animated class="tabs">
      <n-tab-pane name="state" tab="状态">
        <State />
      </n-tab-pane>
      <n-tab-pane name="edit" tab="编辑">
        <Edit />
      </n-tab-pane>
      <n-tab-pane name="upload" tab="上传">
        <Upload />
      </n-tab-pane>
      <n-tab-pane name="introduction" tab="介绍">
        <Introduction />
      </n-tab-pane>
    </n-tabs>
  </n-card>
</template>
<style>
.app{
  width: 100vw;
  height: 100vh;
}
.logo{
  user-select: none;
  margin: 0
}
.tabs span{
  user-select: none;
}
</style>
