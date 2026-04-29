<script setup lang="ts">
import {NInput, NButtonGroup, NButton} from "naive-ui";
import {ref} from "vue";

const value = ref<string>('');
function clearText(){
  value.value = '';
}
function saveText(){
  console.log(value.value);
}
</script>

<template>
    <n-button-group>
      <n-button class="button" type="primary" @click="saveText">
        保存
      </n-button>
      <n-button class="button" type="info" @click="clearText">
        清空
      </n-button>
    </n-button-group>
  <n-input
      v-model:value="value"
      type="textarea"
      placeholder=""
      :autosize="{minRows: 30, maxRows: 90}"
  />
</template>

<style scoped>
.button {
  user-select: none;
}
</style>